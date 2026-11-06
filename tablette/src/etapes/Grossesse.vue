<script setup lang="ts">
// Étape facultative : grossesse, accouchement et développement de la petite
// enfance, pré-remplis par le questionnaire des parents. Rien n'y est obligatoire.
import { DEVELOPPEMENT, questionnaire } from '../bilan'
import { bilan } from '../brouillon'
import Puces from '../composants/Puces.vue'

const { grossesse } = questionnaire
const types = grossesse.types.map((t) => t.libelle)
const choixUniques = [
  { cle: 'terme', titre: 'Terme', options: grossesse.termes.map((t) => t.libelle) },
  { cle: 'voie', titre: 'Voie', options: grossesse.voies.map((v) => v.libelle) },
  { cle: 'forceps', titre: 'Forceps', options: grossesse.forceps.map((f) => f.libelle) },
] as const
</script>

<template>
  <p class="aide">Étape facultative : rien n'est obligatoire pour continuer.</p>

  <section class="carte">
    <h3>Grossesse et accouchement</h3>
    <p class="aide">Type de grossesse (plusieurs choix possibles)</p>
    <Puces v-model="bilan.typesGrossesse" :options="types" />
    <div class="grille">
      <label v-for="choix in choixUniques" :key="choix.cle">{{ choix.titre }}
        <select v-model="bilan[choix.cle]">
          <option value="">— non renseigné —</option>
          <option v-for="option in choix.options" :key="option">{{ option }}</option>
        </select>
      </label>
    </div>
  </section>

  <section class="carte">
    <h3>Développement de la petite enfance</h3>
    <p class="aide">Réponses des parents, reprises telles quelles.</p>
    <label v-for="question in DEVELOPPEMENT" :key="question.cle">{{ question.ecran }}
      <input v-model="bilan[question.cle]" />
    </label>
  </section>
</template>
