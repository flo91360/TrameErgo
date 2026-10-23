<script setup lang="ts">
import { questionnaire } from '../bilan'
import { bilan } from '../brouillon'
import Puces from '../composants/Puces.vue'
</script>

<template>
  <section class="carte">
    <h3>Aménagements scolaires</h3>
    <Puces v-model="bilan.amenagements" :options="questionnaire.amenagements" />
    <label>Autre / aménagement scolaire (un par ligne)
      <textarea v-model="bilan.autreAmenagement" rows="3" />
    </label>
  </section>

  <section class="carte">
    <label>Activités extra-scolaires (séparées par des virgules)
      <input v-model="bilan.activitesExtraScolaires" placeholder="football, piano" />
    </label>
    <label>Activités pendant le temps libre (séparées par des virgules)
      <input v-model="bilan.activitesTempsLibre" placeholder="dessin, jeux vidéo" />
    </label>
    <label>Difficultés pendant les loisirs <input v-model="bilan.difficultesLoisirs" /></label>
  </section>
</template>
