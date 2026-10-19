<script setup lang="ts">
import { computed } from 'vue'
import { calculerAge, datesIncoherentes, lateralites, questionnaire } from '../bilan'
import { bilan } from '../brouillon'
import Segments from '../composants/Segments.vue'

const { identite } = questionnaire
const age = computed(() => calculerAge(bilan.dateNaissance, bilan.datePassation))
</script>

<template>
  <section class="carte">
    <div class="grille">
      <!-- Pas de <label> autour des segments : toucher son texte choisirait le premier segment. -->
      <div class="champ">Sexe
        <Segments v-model="bilan.sexe" etiquette="Sexe"
                  :options="[{ valeur: 'Femme', libelle: 'Fille' }, { valeur: 'Homme', libelle: 'Garçon' }]" />
      </div>
      <div class="champ">Bilan
        <Segments v-model="bilan.trancheAge" etiquette="Bilan"
                  :options="[{ valeur: 'Enfant', libelle: 'Enfant' }, { valeur: 'Ado', libelle: 'Adolescent' }]" />
      </div>
      <label>Prénom <input v-model="bilan.prenom" autocomplete="off" /></label>
      <label>Nom <input v-model="bilan.nom" autocomplete="off" /></label>
      <label>Date de naissance <input v-model="bilan.dateNaissance" type="date" /></label>
      <label>Date de passation <input v-model="bilan.datePassation" type="date" /></label>
    </div>
    <p v-if="age" class="aide">Âge à la passation : {{ age }}</p>
    <p v-if="datesIncoherentes(bilan)" class="alerte">La date de naissance est après la date de passation.</p>
  </section>

  <section class="carte">
    <div class="grille">
      <label>Classe
        <select v-model="bilan.classe">
          <option value="" disabled>— à renseigner —</option>
          <option v-for="c in identite.classes" :key="c">{{ c }}</option>
        </select>
      </label>
      <label>Établissement
        <select v-model="bilan.typeEtablissement">
          <option value="" disabled>— à renseigner —</option>
          <option v-for="t in identite.typesEtablissement" :key="t">{{ t }}</option>
        </select>
      </label>
      <label class="large">Nom de l'établissement <input v-model="bilan.nomEtablissement" /></label>
      <label>Latéralité
        <select v-model="bilan.lateralite">
          <option :value="null" disabled>— à renseigner —</option>
          <option v-for="(l, i) in lateralites(bilan.sexe)" :key="l" :value="i">{{ l }}</option>
        </select>
      </label>
      <label>Mode de garde
        <select v-model="bilan.modeDeGarde">
          <option value="" disabled>— à renseigner —</option>
          <option v-for="m in identite.modesDeGarde" :key="m">{{ m }}</option>
        </select>
      </label>
    </div>
  </section>

  <section class="carte">
    <label class="interrupteur"><input v-model="bilan.enfantUnique" type="checkbox" /> Enfant unique</label>
    <div v-if="!bilan.enfantUnique" class="grille">
      <label>Fratrie <input v-model="bilan.fratrie" placeholder="1 frère et 1 sœur" /></label>
      <div class="champ">Entente
        <Segments v-model="bilan.entente" etiquette="Entente"
                  :options="identite.entente.map((e) => ({ valeur: e.libelle, libelle: e.libelle }))" />
      </div>
    </div>
  </section>

  <section class="carte">
    <div class="grille">
      <label>Médecin traitant <input v-model="bilan.medecinTraitant" placeholder="Nom, sans « Dr »" /></label>
      <label>Ville <input v-model="bilan.ville" /></label>
    </div>
  </section>
</template>
