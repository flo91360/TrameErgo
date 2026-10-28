<script setup lang="ts">
import { questionnaire } from '../bilan'
import { bilan } from '../brouillon'
import Puces from '../composants/Puces.vue'

const { scolarite } = questionnaire
</script>

<template>
  <section class="carte">
    <h3>Comportement en classe</h3>
    <Puces v-model="bilan.comportement" :options="scolarite.comportement" />
  </section>

  <section class="carte">
    <h3>Difficultés en classe</h3>
    <Puces v-model="bilan.difficultes" :options="scolarite.difficultes" />
    <label>Autre <input v-model="bilan.autreDifficulte" /></label>
  </section>

  <section class="carte">
    <h3>Matière(s) préférée(s)</h3>
    <Puces v-model="bilan.matieresPreferees" :options="scolarite.matieres" />
    <label>Autre <input v-model="bilan.autreMatierePreferee" /></label>
  </section>

  <section class="carte">
    <h3>Matières les moins appréciées</h3>
    <Puces v-model="bilan.matieresDetestees" :options="scolarite.matieres" />
    <label>Autre <input v-model="bilan.autreMatiereDetestee" /></label>
  </section>
</template>
