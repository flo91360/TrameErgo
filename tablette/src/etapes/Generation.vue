<script setup lang="ts">
import { computed, ref } from 'vue'
import modeleUrl from '@contenu/bilan.docx?url'
import {
  activitesEnDifficulte, aRenseigner, champs, nomDuFichier, objectifsRetenus, questionnaire,
} from '../bilan'
import { bilan } from '../brouillon'
import { remplirModele, TYPE_DOCX } from '../generer'
import { ajouterAHistorique } from '../historique'
import { choisirSiExiste, enregistrerDansDocuments, existe, nomLibre, ouvrir, surOrdinateur } from '../ordinateur'

defineEmits<{ terminer: [] }>()

// Les écrans ne laissent pas passer un bilan incomplet ; ceci protège un
// brouillon d'une version précédente, qui pourrait l'être.
const manquants = computed(() => aRenseigner(bilan))

// Mêmes calculs que le bilan Word : un objectif dont l'activité est revenue
// à « Rien à signaler » n'est pas compté.
const resume = computed(() => [
  ['Patient', `${bilan.prenom} ${bilan.nom}`.trim() || '—'],
  ['Âge', champs(bilan).age || '—'],
  ['Troubles', String(bilan.troubles.length + (bilan.autreTrouble.trim() ? 1 : 0))],
  ...questionnaire.otHope.domaines.map((d) =>
    [d.titre, `${activitesEnDifficulte(bilan, d.id).length} activité(s) signalée(s)`]),
  ['Objectifs finaux', String(objectifsRetenus(bilan, bilan.objectifsFinaux).length)],
])

const fichier = ref<File | null>(null)
const chemin = ref('')
const erreur = ref('')
const enCours = ref(false)
const partageable = computed(() => !!fichier.value && !!navigator.canShare?.({ files: [fichier.value] }))

function message(e: unknown): string {
  return e instanceof Error ? e.message : String(e)
}

async function generer() {
  if (enCours.value || manquants.value.length) return
  enCours.value = true
  erreur.value = ''
  fichier.value = null
  chemin.value = ''
  try {
    let docx: Uint8Array
    try {
      const reponse = await fetch(modeleUrl)
      if (!reponse.ok) throw new Error(`modèle Word introuvable (erreur ${reponse.status})`)
      docx = remplirModele(await reponse.arrayBuffer(), champs(bilan))
    } catch (e) {
      erreur.value = `Le bilan n'a pas pu être créé : ${message(e)}`
      return
    }
    ajouterAHistorique(bilan)
    if (!surOrdinateur) {
      fichier.value = new File([docx as BlobPart], nomDuFichier(bilan), { type: TYPE_DOCX })
      telecharger()
      return
    }
    try {
      const nom = await nomSansEcraser(nomDuFichier(bilan))
      if (!nom) return // Création annulée : rien n'est écrit.
      chemin.value = await enregistrerDansDocuments(nom, docx)
    } catch (e) {
      erreur.value = `Le bilan n'a pas pu être enregistré dans Documents\\TrameErgo : ${message(e)}`
        + ' (est-il déjà ouvert dans Word ?)'
      return
    }
    fichier.value = new File([docx as BlobPart], chemin.value.split(/[\\/]/).pop()!, { type: TYPE_DOCX })
    await ouvrirDansWord()
  } finally {
    enCours.value = false
  }
}

// Un bilan déjà enregistré a pu être complété dans Word : le remplacer
// effacerait ce travail. On demande : remplacer, garder les deux (copie
// numérotée) ou annuler (null).
async function nomSansEcraser(nom: string): Promise<string | null> {
  if (!(await existe(nom))) return nom
  const choix = await choisirSiExiste(nom)
  if (choix === 'annuler') return null
  return choix === 'remplacer' ? nom : nomLibre(nom)
}

async function ouvrirDansWord() {
  erreur.value = ''
  try {
    await ouvrir(chemin.value)
  } catch (e) {
    erreur.value = `Le bilan est enregistré, mais Word n'a pas pu l'ouvrir : ${message(e)}.`
      + ' Il se trouve dans Documents\\TrameErgo.'
  }
}

function telecharger() {
  if (!fichier.value) return
  const lien = document.createElement('a')
  lien.href = URL.createObjectURL(fichier.value)
  lien.download = fichier.value.name
  lien.click()
  setTimeout(() => URL.revokeObjectURL(lien.href), 60_000)
}

async function partager() {
  if (fichier.value) await navigator.share({ files: [fichier.value], title: fichier.value.name }).catch(() => {})
}

</script>

<template>
  <section class="carte">
    <dl class="resume">
      <template v-for="[titre, valeur] in resume" :key="titre">
        <dt>{{ titre }}</dt><dd>{{ valeur }}</dd>
      </template>
    </dl>
    <p v-if="manquants.length" class="alerte">Il manque {{ manquants.join(', ') }}.</p>
  </section>

  <section class="carte actions">
    <button type="button" class="principal" :disabled="enCours || !!manquants.length" @click="generer">
      {{ enCours ? 'Création du bilan…' : 'Créer le bilan Word' }}
    </button>
    <template v-if="fichier && surOrdinateur">
      <p class="aide">Bilan enregistré : {{ chemin }}</p>
      <button type="button" class="secondaire" @click="ouvrirDansWord">Ouvrir dans Word</button>
    </template>
    <template v-else-if="fichier">
      <p class="aide">{{ fichier.name }} est créé sur cet appareil.</p>
      <button type="button" class="secondaire" @click="telecharger">Enregistrer à nouveau</button>
      <button v-if="partageable" type="button" class="secondaire" @click="partager">Partager (Word, Mail…)</button>
    </template>
    <p v-if="erreur" class="alerte">{{ erreur }}</p>
  </section>

  <section class="carte">
    <p class="aide">
      Chaque bilan créé est gardé dans l'historique de cet appareil : rien n'est envoyé sur Internet.
    </p>
    <button type="button" class="secondaire" @click="$emit('terminer')">Retour à l'accueil</button>
  </section>
</template>
