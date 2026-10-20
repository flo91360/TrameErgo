<script setup lang="ts">
import { computed } from 'vue'
import { entame } from '../bilan'
import { bilan } from '../brouillon'
import { historique } from '../historique'

defineEmits<{ nouveau: []; reprendre: []; historique: [] }>()

const enCours = computed(() => entame(bilan))
const nombre = computed(() => historique.value.length)
</script>

<template>
  <h2>Que voulez-vous faire ?</h2>
  <div class="accueil">
    <button type="button" class="action" @click="$emit('nouveau')">
      <strong>Nouveau bilan</strong>
      <span>Commencer un bilan vide.</span>
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
  <p class="aide">Les réponses restent sur cet appareil : rien n'est envoyé sur Internet.</p>
</template>
