<script setup lang="ts">
import { computed } from 'vue'
import modeleUrl from '@contenu/bilan.docx?url'
import {
  activitesEnDifficulte, aRenseigner, champs, nomDuFichier, objectifsRetenus, questionnaire,
} from '../bilan'
import { bilan } from '../brouillon'
import CreerDocument from '../composants/CreerDocument.vue'
import { ajouterAHistorique } from '../historique'

defineEmits<{ terminer: [] }>()

// Les écrans ne laissent pas passer un bilan incomplet ; ceci protège un
// brouillon d'une version précédente, qui pourrait l'être.
const manquants = computed(() => aRenseigner(bilan))

// Mêmes calculs que le bilan Word : un objectif dont l'activité est revenue
// à « Rien à signaler » n'est pas compté.
const resume = computed(() => [
  ['Patient', `${bilan.prenom} ${bilan.nom}`.trim() || '—'],
  ['Âge', champs(bilan).age || '—'],
  ['Troubles', String(bilan.troubles.length + (bilan.autreTrouble.trim() ? 1 : 0))],
  ...questionnaire.otHope.domaines.map((d) =>
    [d.titre, `${activitesEnDifficulte(bilan, d.id).length} activité(s) signalée(s)`]),
  ['Objectifs finaux', String(objectifsRetenus(bilan, bilan.objectifsFinaux).length)],
])

const nomBilan = () => nomDuFichier(bilan)
const valeursBilan = () => champs(bilan)
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
    <CreerDocument libelle="Créer le bilan Word" libelle-en-cours="Création du bilan…" quoi="Le bilan"
                   :modele="modeleUrl" :nom="nomBilan" :valeurs="valeursBilan"
                   :desactive="!!manquants.length" @cree="ajouterAHistorique(bilan)" />
  </section>

  <section class="carte">
    <p class="aide">
      Chaque bilan créé est gardé dans l'historique de cet appareil : rien n'est envoyé sur Internet.
    </p>
    <button type="button" class="secondaire" @click="$emit('terminer')">Retour à l'accueil</button>
  </section>
</template>
