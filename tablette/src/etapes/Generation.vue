<script setup lang="ts">
import { computed, ref } from 'vue'
import modeleUrl from '@contenu/bilan.docx?url'
import { activitesEnDifficulte, champs, nomDuFichier, questionnaire } from '../bilan'
import { bilan, nouveauBilanVide } from '../brouillon'
import { remplirModele, TYPE_DOCX } from '../generer'
import { enregistrerDansDocuments, ouvrir, surOrdinateur } from '../ordinateur'

const emit = defineEmits<{ recommencer: [] }>()

const manquants = computed(() => [
  !bilan.prenom.trim() && 'le prénom',
  !bilan.nom.trim() && 'le nom',
  !bilan.dateNaissance && 'la date de naissance',
].filter(Boolean) as string[])

const resume = computed(() => [
  ['Patient', `${bilan.prenom} ${bilan.nom}`.trim() || '—'],
  ['Âge', champs(bilan).age || '—'],
  ['Troubles', String(bilan.troubles.length + (bilan.autreTrouble.trim() ? 1 : 0))],
  ...questionnaire.otHope.domaines.map((d) => [d.titre, `${activitesEnDifficulte(bilan, d.id).length} activité(s) signalée(s)`]),
  ['Objectifs finaux', String(bilan.objectifsFinaux.length)],
])

const fichier = ref<File | null>(null)
const chemin = ref('')
const erreur = ref('')
const partageable = computed(() => !!fichier.value && !!navigator.canShare?.({ files: [fichier.value] }))

async function generer() {
  erreur.value = ''
  try {
    const modele = await (await fetch(modeleUrl)).arrayBuffer()
    const docx = remplirModele(modele, champs(bilan))
    fichier.value = new File([docx as BlobPart], nomDuFichier(bilan), { type: TYPE_DOCX })
    if (surOrdinateur) {
      chemin.value = await enregistrerDansDocuments(fichier.value.name, docx)
      await ouvrir(chemin.value)
    } else {
      telecharger()
    }
  } catch (e) {
    erreur.value = `Le bilan n'a pas pu être créé : ${e instanceof Error ? e.message : e}`
      + (surOrdinateur ? ' (est-il déjà ouvert dans Word ?)' : '')
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
  </section>

  <section class="carte actions">
    <button type="button" class="principal" @click="generer">Créer le bilan Word</button>
    <template v-if="fichier && surOrdinateur">
      <p class="aide">Bilan enregistré : {{ chemin }}</p>
      <button type="button" class="secondaire" @click="ouvrir(chemin)">Ouvrir dans Word</button>
    </template>
    <template v-else-if="fichier">
      <p class="aide">{{ fichier.name }} est créé sur la tablette.</p>
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
