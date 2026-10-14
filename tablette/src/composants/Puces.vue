<script setup lang="ts">
// Choix multiple en grosses puces, faciles à toucher.
const props = defineProps<{ options: readonly string[]; desactive?: boolean }>()
const choisis = defineModel<string[]>({ required: true })

function basculer(option: string) {
  choisis.value = choisis.value.includes(option)
    ? choisis.value.filter((o) => o !== option)
    : props.options.filter((o) => o === option || choisis.value.includes(o))
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
      :disabled="desactive"
      @click="basculer(option)"
    >
      {{ option }}
    </button>
  </div>
</template>
