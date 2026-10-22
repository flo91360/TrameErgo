<script setup lang="ts">
import { computed } from 'vue'
import { entame } from '../bilan'
import { bilan } from '../brouillon'
import { historique } from '../historique'
import { configure } from '../questionnaireParents'

defineEmits<{ nouveau: []; reprendre: []; historique: []; reglages: [] }>()

const enCours = computed(() => entame(bilan))
const nombre = computed(() => historique.value.length)
</script>

<template>
  <h2>Que voulez-vous faire ?</h2>
  <div class="accueil">
    <button type="button" class="action" @click="$emit('nouveau')">
      <strong>Nouveau bilan</strong>
      <span>Saisir le nom de l'enfant, puis importer le questionnaire des parents s'il a été rempli.</span>
    </button>
    <button type="button" class="action" :disabled="!enCours" @click="$emit('reprendre')">
      <strong>Reprendre le bilan en cours</strong>
      <span v-if="enCours">{{ bilan.prenom }} {{ bilan.nom }}</span>
      <span v-else>Aucun bilan en cours.</span>
    </button>
    <button type="button" class="action" @click="$emit('historique')">
      <strong>Historique des bilans</strong>
      <span>
        {{ nombre ? `${nombre} bilan${nombre > 1 ? 's' : ''} créé${nombre > 1 ? 's' : ''} sur cet appareil`
          : 'Aucun bilan créé pour l\'instant' }}.
        Rouvrir, réévaluer, sauvegarder.
      </span>
    </button>
  </div>
  <p class="aide">
    Questionnaire des parents : {{ configure ? 'relié' : 'non relié' }}.
    <button type="button" class="lien" @click="$emit('reglages')">Régler</button>
  </p>
  <p class="aide">
    Les réponses restent sur cet appareil.
    {{ configure
      ? 'Seuls le prénom et le nom de l\'enfant sont envoyés à votre script Google, pour retrouver le questionnaire des parents.'
      : 'Rien n\'est envoyé sur Internet.' }}
  </p>
</template>
