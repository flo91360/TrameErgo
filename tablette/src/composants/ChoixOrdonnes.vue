<script setup lang="ts">
// Choix d'au plus « maximum » éléments, numérotés dans l'ordre du toucher.
const props = defineProps<{ options: readonly string[]; maximum: number }>()
const choisis = defineModel<string[]>({ required: true })

function basculer(option: string) {
  if (choisis.value.includes(option)) choisis.value = choisis.value.filter((o) => o !== option)
  else if (choisis.value.length < props.maximum) choisis.value = [...choisis.value, option]
}
</script>

<template>
  <div class="puces">
    <button
      v-for="option in options"
      :key="option"
      type="button"
      class="puce"
      :class="{ choisie: choisis.includes(option) }"
      :aria-pressed="choisis.includes(option)"
      :disabled="!choisis.includes(option) && choisis.length >= maximum"
      @click="basculer(option)"
    >
      <span v-if="choisis.includes(option)" class="rang">{{ choisis.indexOf(option) + 1 }}</span>
      {{ option }}
    </button>
  </div>
</template>
