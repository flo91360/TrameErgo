<script setup lang="ts">
import { computed, ref } from 'vue'
import modeleUrl from '@contenu/bilan.docx?url'
import { activitesEnDifficulte, champs, datesIncoherentes, nomDuFichier, objectifsRetenus, questionnaire } from '../bilan'
import { bilan, nouveauBilanVide } from '../brouillon'
import { remplirModele, TYPE_DOCX } from '../generer'
import { enregistrerDansDocuments, existe, nomLibre, ouvrir, surOrdinateur } from '../ordinateur'

const emit = defineEmits<{ recommencer: [] }>()

const manquants = computed(() => [
  !bilan.prenom.trim() && 'le prénom',
  !bilan.nom.trim() && 'le nom',
  !bilan.dateNaissance && 'la date de naissance',
  !bilan.datePassation && 'la date de passation',
].filter(Boolean) as string[])

// Mêmes calculs que le bilan Word : un objectif dont l'activité est revenue
// à « Rien à signaler » n'est pas compté.
const resume = computed(() => [
  ['Patient', `${bilan.prenom} ${bilan.nom}`.trim() || '—'],
  ['Âge', champs(bilan).age || '—'],
  ['Troubles', String(bilan.troubles.length + (bilan.autreTrouble.trim() ? 1 : 0))],
  ...questionnaire.otHope.domaines.map((d) => [d.titre, `${activitesEnDifficulte(bilan, d.id).length} activité(s) signalée(s)`]),
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
  if (enCours.value) return
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
    if (!surOrdinateur) {
      fichier.value = new File([docx as BlobPart], nomDuFichier(bilan), { type: TYPE_DOCX })
      telecharger()
      return
    }
    try {
      chemin.value = await enregistrerDansDocuments(await nomSansEcraser(nomDuFichier(bilan)), docx)
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
// effacerait ce travail. Sans accord, une copie numérotée est créée à côté.
async function nomSansEcraser(nom: string): Promise<string> {
  if (!(await existe(nom))) return nom
  const remplacer = confirm(`${nom} existe déjà dans Documents\\TrameErgo et a peut-être été complété dans Word.\n\n`
    + 'OK : le remplacer (les modifications faites dans Word seront perdues).\n'
    + 'Annuler : enregistrer une copie à côté.')
  return remplacer ? nom : nomLibre(nom)
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

function recommencer() {
  if (confirm('Effacer ce bilan de cet appareil et en commencer un nouveau ?')) {
    nouveauBilanVide()
    fichier.value = null
    chemin.value = ''
    erreur.value = ''
    emit('recommencer')
  }
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
    <p v-if="datesIncoherentes(bilan)" class="alerte">
      La date de naissance est après la date de passation : l'âge ne peut pas être calculé.
    </p>
  </section>

  <section class="carte actions">
    <button type="button" class="principal" :disabled="enCours" @click="generer">
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
    <p class="aide">Les réponses restent sur cet appareil, jusqu'au prochain bilan : rien n'est envoyé sur Internet.</p>
    <button type="button" class="danger" @click="recommencer">Nouveau bilan</button>
  </section>
</template>
