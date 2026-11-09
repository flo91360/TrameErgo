<script setup lang="ts">
import { computed, onBeforeUnmount, ref, watch } from 'vue'
import { nouveauBilan, type Bilan } from '../bilan'
import { chercher, configure, importer, preRemplir, type Recherche } from '../questionnaireParents'

const emit = defineEmits<{ commencer: [bilan: Bilan, activites?: number]; reglages: [] }>()

const prenom = ref('')
const nom = ref('')
const recherche = ref<Recherche | null>(null)
const enCours = ref(false)
/** Importation des réponses du questionnaire choisi, après la recherche. */
const importation = ref(false)
const erreurImport = ref('')
/** Questionnaire choisi quand les parents en ont envoyé plusieurs. */
const choisi = ref(0)
const complet = computed(() => !!prenom.value.trim() && !!nom.value.trim())
const trouves = computed(() => recherche.value?.etat === 'trouve' ? recherche.value.envois : [])

let minuteur: ReturnType<typeof setTimeout> | undefined
/** Numéro de la dernière recherche : une réponse arrivée pour un nom déjà changé est ignorée. */
let numero = 0

// Recherche dès que le prénom et le nom sont saisis, après une courte pause de frappe.
watch([prenom, nom], () => {
  clearTimeout(minuteur)
  numero += 1
  enCours.value = false
  recherche.value = null
  choisi.value = 0
  importation.value = false
  erreurImport.value = ''
  if (configure.value && complet.value) minuteur = setTimeout(verifier, 600)
})
onBeforeUnmount(() => clearTimeout(minuteur))
watch(choisi, () => { erreurImport.value = '' })

async function verifier() {
  const demande = ++numero
  enCours.value = true
  const resultat = await chercher(prenom.value, nom.value)
  if (demande !== numero) return
  enCours.value = false
  recherche.value = resultat
}

const envoi = (iso: string) =>
  new Intl.DateTimeFormat('fr-FR', { dateStyle: 'long', timeStyle: 'short' }).format(new Date(iso))

function depart(): Bilan {
  return { ...nouveauBilan(), prenom: prenom.value.trim(), nom: nom.value.trim() }
}

async function importerReponses() {
  const demande = numero
  importation.value = true
  erreurImport.value = ''
  const resultat = await importer(trouves.value[choisi.value], prenom.value, nom.value)
  if (demande !== numero) return
  importation.value = false
  if (resultat.etat !== 'importe') {
    erreurImport.value = resultat.raison
    return
  }
  const { bilan, activites } = preRemplir(depart(), resultat.questionnaire)
  emit('commencer', bilan, activites)
}
</script>

<template>
  <h2>Nouveau bilan</h2>
  <section class="carte">
    <div class="grille">
      <label>Prénom <input v-model="prenom" autocomplete="off" /></label>
      <label>Nom <input v-model="nom" autocomplete="off" /></label>
    </div>

    <p class="questionnaire" role="status">
      <template v-if="!configure">
        Questionnaire des parents non relié à cet appareil.
        <button type="button" class="lien" @click="emit('reglages')">Le relier</button>
      </template>
      <span v-else-if="!complet" class="aide">
        Saisir le prénom et le nom pour chercher le questionnaire des parents.
      </span>
      <template v-else-if="enCours || !recherche">
        <span class="indicateur attente" aria-hidden="true">…</span> Recherche du questionnaire des parents…
      </template>
      <template v-else-if="recherche.etat === 'trouve'">
        <span class="indicateur trouve" aria-hidden="true">✓</span>
        <span v-if="trouves.length === 1">Questionnaire des parents trouvé, envoyé le {{ envoi(trouves[0].envoi) }}.</span>
        <span v-else>{{ trouves.length }} questionnaires des parents à ce nom.</span>
      </template>
      <template v-else-if="recherche.etat === 'absent'">
        <span class="indicateur absent" aria-hidden="true">✗</span> Aucun questionnaire des parents à ce nom.
      </template>
      <template v-else>
        <span class="indicateur injoignable" aria-hidden="true">?</span>
        Questionnaire des parents non vérifié : {{ recherche.raison }}.
        <button type="button" class="lien" @click="verifier">Réessayer</button>
      </template>
    </p>

    <label v-if="trouves.length > 1">Questionnaire à importer
      <select v-model="choisi" :disabled="importation">
        <option v-for="(q, i) in trouves" :key="q.envoi" :value="i">Envoyé le {{ envoi(q.envoi) }}</option>
      </select>
    </label>

    <p v-if="importation" class="questionnaire" role="status">
      <span class="indicateur attente" aria-hidden="true">…</span> Importation des réponses…
    </p>
    <p v-else-if="erreurImport" class="questionnaire" role="alert">
      <span class="indicateur injoignable" aria-hidden="true">?</span>
      Réponses non importées : {{ erreurImport }}.
      <button type="button" class="lien" @click="importerReponses">Réessayer</button>
    </p>

    <div class="boutons">
      <button v-if="trouves.length" type="button" class="principal" :disabled="importation" @click="importerReponses">
        Importer et pré-remplir
      </button>
      <button type="button" :class="trouves.length ? 'secondaire' : 'principal'" :disabled="importation"
        @click="emit('commencer', depart())">
        {{ trouves.length ? 'Commencer sans le questionnaire' : 'Commencer le bilan' }}
      </button>
    </div>
  </section>
</template>
