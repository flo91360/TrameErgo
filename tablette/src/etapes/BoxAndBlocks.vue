<script setup lang="ts">
// Test de motricité Box and Blocks, rempli pendant le test : pour chaque main,
// les blocs déplacés en une minute, la douleur et les observations. Le nombre
// de blocs prend la couleur de son niveau ; l'écart-type calculé n'est écrit
// que dans le bilan Word.
import { computed } from 'vue'
import {
  choixObservation, coteDeLaMain, coteDominant, MAINS, NIVEAUX_BB, niveauDeLaMain, nombreFrancais, normeDeLaMain,
  OBSERVATIONS_BB, trancheNormes, accord, type Cote, type Main,
} from '../bilan'
import { bilan } from '../brouillon'
import Puces from '../composants/Puces.vue'
import Segments from '../composants/Segments.vue'

const TITRES: Record<Main, string> = { dominante: 'Main dominante', nonDominante: 'Main non dominante' }
const DOULEURS = Array.from({ length: 11 }, (_, i) => ({ valeur: String(i), libelle: String(i) }))

const cote = computed({
  get: () => coteDominant(bilan),
  set: (valeur: Cote | '') => { bilan.boxAndBlocks.cote = valeur },
})
const tranche = computed(() => trancheNormes(bilan))

function titre(main: Main): string {
  const c = coteDeLaMain(bilan, main)
  return c ? `${TITRES[main]} (${c})` : TITRES[main]
}

function attendu(main: Main): string {
  const norme = normeDeLaMain(bilan, main)
  return norme
    ? `moyenne ${nombreFrancais(norme.moyenne)} blocs, écart-type ${nombreFrancais(norme.ecartType)}`
    : '—'
}

function niveau(main: Main) {
  const id = niveauDeLaMain(bilan, main)
  return NIVEAUX_BB.find((n) => n.id === id)
}

function saisirBlocs(main: Main, texte: string) {
  const nombre = Number.parseInt(texte, 10)
  bilan.boxAndBlocks[main].blocs = Number.isNaN(nombre) ? null : Math.min(Math.max(nombre, 0), 999)
}

function douleur(main: Main): string {
  const valeur = bilan.boxAndBlocks[main].douleur
  return valeur === null ? '' : String(valeur)
}

function choisirDouleur(main: Main, valeur: string) {
  bilan.boxAndBlocks[main].douleur = valeur === '' ? null : Number(valeur)
}

/** Observations simples, montrées accordées au sexe, en une rangée de puces. */
const simples = OBSERVATIONS_BB.filter((o) => !o.choix)
function simplesAffichees() {
  return simples.map((o) => accord(bilan, o.libelle, o.feminin ?? o.libelle))
}
function simplesChoisies(main: Main): string[] {
  return simples.filter((o) => bilan.boxAndBlocks[main].observations.includes(o.libelle))
    .map((o) => accord(bilan, o.libelle, o.feminin ?? o.libelle))
}
function choisirSimples(main: Main, affichees: string[]) {
  const mesure = bilan.boxAndBlocks[main]
  const gardees = mesure.observations.filter((o) => !simples.some((s) => s.libelle === o))
  const nouvelles = simples.filter((o) => affichees.includes(accord(bilan, o.libelle, o.feminin ?? o.libelle)))
    .map((o) => o.libelle)
  mesure.observations = ordonner([...gardees, ...nouvelles])
}

/** Observations à préciser (« Prise » : tridigitale, bidigitale…) : une rangée de puces par observation. */
const aPreciser = OBSERVATIONS_BB.filter((o) => o.choix)
function choisis(main: Main, index: number): string[] {
  const observation = aPreciser[index]
  return (observation.choix ?? [])
    .filter((c) => bilan.boxAndBlocks[main].observations.includes(choixObservation(observation, c)))
}
function choisir(main: Main, index: number, valeurs: string[]) {
  const observation = aPreciser[index]
  const mesure = bilan.boxAndBlocks[main]
  const autres = mesure.observations.filter((o) => !o.startsWith(`${observation.libelle} : `))
  mesure.observations = ordonner([...autres, ...valeurs.map((c) => choixObservation(observation, c))])
}

/** Dans l'ordre du questionnaire, comme dans le bilan. */
function ordonner(valeurs: string[]): string[] {
  return OBSERVATIONS_BB.flatMap((o) => o.choix ? o.choix.map((c) => choixObservation(o, c)) : [o.libelle])
    .filter((o) => valeurs.includes(o))
}
</script>

<template>
  <p class="aide">
    Étape facultative, remplie pendant le test. Blocs déplacés en une minute avec chaque main.
  </p>

  <section class="carte">
    <div class="grille">
      <div class="champ">Main dominante
        <Segments v-model="cote" etiquette="Main dominante"
                  :options="[{ valeur: 'droite', libelle: 'Droite' }, { valeur: 'gauche', libelle: 'Gauche' }]" />
      </div>
      <div class="champ">Normes
        <span v-if="tranche" class="normes">
          {{ bilan.sexe === 'Homme' ? 'Garçons' : 'Filles' }} de {{ tranche.ageMin }} à {{ tranche.ageMax }} ans
        </span>
        <span v-else class="alerte">Âge non couvert par les normes (date de naissance à l'étape Patient).</span>
      </div>
    </div>
    <p v-if="!cote" class="aide">Choisir la main dominante : les normes dépendent du côté.</p>
  </section>

  <section v-for="main in MAINS" :key="main" class="carte box-and-blocks">
    <h3>{{ titre(main) }}</h3>
    <div class="grille">
      <label>Blocs en 1 minute ({{ TITRES[main].toLowerCase() }})
        <input :value="bilan.boxAndBlocks[main].blocs ?? ''" class="blocs" type="number" inputmode="numeric"
               min="0" max="999" step="1" :class="niveau(main) && `niveau-${niveau(main)!.id}`"
               :style="niveau(main) && { color: niveau(main)!.couleur, borderColor: niveau(main)!.couleur }"
               @input="saisirBlocs(main, ($event.target as HTMLInputElement).value)" />
      </label>
      <div class="champ">Attendu à son âge
        <span class="normes">{{ attendu(main) }}</span>
        <span v-if="niveau(main)" class="niveau-bb" :style="{ color: niveau(main)!.couleur }">
          {{ niveau(main)!.libelle }}
        </span>
      </div>
    </div>

    <div class="champ">Douleur (EN de 0 à 10)
      <Segments :model-value="douleur(main)" :options="DOULEURS" :etiquette="`Douleur, ${TITRES[main].toLowerCase()}`"
                @update:model-value="choisirDouleur(main, $event)" />
    </div>
    <label v-if="(bilan.boxAndBlocks[main].douleur ?? 0) > 0">Localisation de la douleur
      ({{ TITRES[main].toLowerCase() }})
      <input v-model="bilan.boxAndBlocks[main].localisationDouleur" placeholder="du poignet, de l’épaule…" />
    </label>

    <h4>Observations</h4>
    <div v-for="(observation, i) in aPreciser" :key="observation.libelle" class="observation">
      <span class="libelle">{{ observation.libelle }}</span>
      <Puces :model-value="choisis(main, i)" :options="observation.choix ?? []"
             @update:model-value="choisir(main, i, $event)" />
    </div>
    <Puces :model-value="simplesChoisies(main)" :options="simplesAffichees()"
           @update:model-value="choisirSimples(main, $event)" />
    <p class="aide">La douleur (ou « Aucune douleur ») s'ajoute d'elle-même aux observations du bilan.</p>
  </section>
</template>
