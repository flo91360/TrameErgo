<script setup lang="ts">
// Choix unique en segments (boutons accolés).
defineProps<{ options: readonly { valeur: string; libelle: string }[]; etiquette?: string }>()
const valeur = defineModel<string>({ required: true })
</script>

<template>
  <div class="segments" role="radiogroup" :aria-label="etiquette">
    <button
      v-for="option in options"
      :key="option.valeur"
      type="button"
      role="radio"
      :aria-checked="valeur === option.valeur"
      :class="{ choisi: valeur === option.valeur, ['niveau-' + (option.valeur || 'rien')]: true }"
      @click="valeur = option.valeur"
    >
      {{ option.libelle }}
    </button>
  </div>
</template>
