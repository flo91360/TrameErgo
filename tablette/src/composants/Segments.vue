<script setup lang="ts">
// Choix unique en segments (boutons accolés).
import { computed } from 'vue'

const props = defineProps<{ options: readonly { valeur: string; libelle: string }[]; etiquette?: string }>()
const valeur = defineModel<string>({ required: true })

// Clavier (Windows) : comme un groupe de boutons radio, un seul arrêt de
// tabulation (le choix en cours, sinon le premier) et les flèches pour changer.
const boutons: HTMLButtonElement[] = []
const tabulable = computed(() => Math.max(0, props.options.findIndex((o) => o.valeur === valeur.value)))

function deplacer(depuis: number, pas: number) {
  const i = (depuis + pas + props.options.length) % props.options.length
  valeur.value = props.options[i].valeur
  boutons[i]?.focus()
}
</script>

<template>
  <div class="segments" role="radiogroup" :aria-label="etiquette">
    <button
      v-for="(option, i) in options"
      :key="option.valeur"
      :ref="(el) => { boutons[i] = el as HTMLButtonElement }"
      type="button"
      role="radio"
      :aria-checked="valeur === option.valeur"
      :tabindex="i === tabulable ? 0 : -1"
      :class="{ choisi: valeur === option.valeur, ['niveau-' + (option.valeur || 'rien')]: true }"
      @click="valeur = option.valeur"
      @keydown.right.prevent="deplacer(i, 1)"
      @keydown.down.prevent="deplacer(i, 1)"
      @keydown.left.prevent="deplacer(i, -1)"
      @keydown.up.prevent="deplacer(i, -1)"
    >
      {{ option.libelle }}
    </button>
  </div>
</template>
