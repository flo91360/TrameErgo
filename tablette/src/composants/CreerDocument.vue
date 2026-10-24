<script setup lang="ts">
// Bouton de création d'un document Word (le bilan) : rempli sur
// l'appareil, puis enregistré dans Documents\TrameErgo et ouvert dans Word
// (Windows), ou téléchargé et partageable (tablette).
import { computed, ref } from 'vue'
import { remplirModele, TYPE_DOCX } from '../generer'
import { choisirSiExiste, enregistrerDansDocuments, existe, nomLibre, ouvrir, surOrdinateur } from '../ordinateur'

const props = defineProps<{
  libelle: string
  libelleEnCours: string
  /** « Le bilan » : sujet des messages. */
  quoi: string
  /** « e » si quoi est féminin : « créée », « enregistrée ». */
  accord?: string
  modele: string
  nom: () => string
  valeurs: () => Record<string, string>
  desactive?: boolean
}>()

const emit = defineEmits<{ cree: [] }>()

const fichier = ref<File | null>(null)
const chemin = ref('')
const erreur = ref('')
const enCours = ref(false)
const partageable = computed(() => !!fichier.value && !!navigator.canShare?.({ files: [fichier.value] }))
const e = computed(() => props.accord ?? '')

function message(e: unknown): string {
  return e instanceof Error ? e.message : String(e)
}

async function creer() {
  if (enCours.value || props.desactive) return
  enCours.value = true
  erreur.value = ''
  fichier.value = null
  chemin.value = ''
  try {
    let docx: Uint8Array
    try {
      const reponse = await fetch(props.modele)
      if (!reponse.ok) throw new Error(`modèle Word introuvable (erreur ${reponse.status})`)
      docx = remplirModele(await reponse.arrayBuffer(), props.valeurs())
    } catch (err) {
      erreur.value = `${props.quoi} n'a pas pu être créé${e.value} : ${message(err)}`
      return
    }
    emit('cree')
    if (!surOrdinateur) {
      fichier.value = new File([docx as BlobPart], props.nom(), { type: TYPE_DOCX })
      telecharger()
      return
    }
    try {
      const nom = await nomSansEcraser(props.nom())
      if (!nom) return // Création annulée : rien n'est écrit.
      chemin.value = await enregistrerDansDocuments(nom, docx)
    } catch (err) {
      erreur.value = `${props.quoi} n'a pas pu être enregistré${e.value} dans Documents\\TrameErgo : ${message(err)}`
        + ' (est-il déjà ouvert dans Word ?)'
      return
    }
    fichier.value = new File([docx as BlobPart], chemin.value.split(/[\\/]/).pop()!, { type: TYPE_DOCX })
    await ouvrirDansWord()
  } finally {
    enCours.value = false
  }
}

// Un document déjà enregistré a pu être complété dans Word : le remplacer
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
  } catch (err) {
    erreur.value = `${props.quoi} est enregistré${e.value}, mais Word n'a pas pu l'ouvrir : ${message(err)}.`
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
  <button type="button" class="principal" :disabled="enCours || desactive" @click="creer">
    {{ enCours ? libelleEnCours : libelle }}
  </button>
  <template v-if="fichier && surOrdinateur">
    <p class="aide">{{ quoi }} enregistré{{ e }} : {{ chemin }}</p>
    <button type="button" class="secondaire" @click="ouvrirDansWord">Ouvrir dans Word</button>
  </template>
  <template v-else-if="fichier">
    <p class="aide">{{ fichier.name }} est créé sur cet appareil.</p>
    <button type="button" class="secondaire" @click="telecharger">Enregistrer à nouveau</button>
    <button v-if="partageable" type="button" class="secondaire" @click="partager">Partager (Word, Mail…)</button>
  </template>
  <p v-if="erreur" class="alerte">{{ erreur }}</p>
</template>
