<script setup lang="ts">
import { AUTRE_PERSONNE_DEMANDEUSE, questionnaire } from '../bilan'
import { bilan } from '../brouillon'
import Puces from '../composants/Puces.vue'

const { demande } = questionnaire
</script>

<template>
  <section class="carte">
    <div class="grille">
      <label>Personne demandeuse
        <select v-model="bilan.personneDemandeuse">
          <option value="" disabled>— à renseigner —</option>
          <option v-for="p in demande.personnesDemandeuses" :key="p">{{ p }}</option>
        </select>
      </label>
      <label v-if="bilan.personneDemandeuse === AUTRE_PERSONNE_DEMANDEUSE">Autre personne demandeuse
        <input v-model="bilan.autrePersonneDemandeuse" placeholder="ex. : l'orthoptiste" />
      </label>
      <label>2ème personne demandeuse (facultatif)
        <select v-model="bilan.deuxiemePersonneDemandeuse">
          <option value="">— aucune —</option>
          <option v-for="p in demande.personnesDemandeuses" :key="p">{{ p }}</option>
        </select>
      </label>
      <label v-if="bilan.deuxiemePersonneDemandeuse === AUTRE_PERSONNE_DEMANDEUSE">Autre 2ème personne demandeuse
        <input v-model="bilan.autreDeuxiemePersonneDemandeuse" placeholder="ex. : l'orthoptiste" />
      </label>
      <label>Dossier MDPH
        <select v-model="bilan.dossierMdph">
          <option value="" disabled>— à renseigner —</option>
          <option v-for="d in demande.dossierMdph" :key="d">{{ d }}</option>
        </select>
      </label>
    </div>
  </section>

  <section class="carte">
    <h3>Motifs</h3>
    <Puces v-model="bilan.motifs" :options="demande.motifs" />
    <label>Autre motif <input v-model="bilan.autreMotif" /></label>
  </section>

  <section class="carte">
    <h3>Anamnèse / troubles</h3>
    <Puces v-model="bilan.troubles" :options="demande.troubles" />
    <label>Autre trouble <input v-model="bilan.autreTrouble" /></label>
  </section>
</template>
