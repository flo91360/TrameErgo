<script setup lang="ts">
import { computed } from 'vue'
import { questionnaire } from '../bilan'
import { bilan } from '../brouillon'
import Segments from '../composants/Segments.vue'

const props = defineProps<{ domaine: string }>()
const definition = computed(() => questionnaire.otHope.domaines.find((d) => d.id === props.domaine)!)
// « Rien à signaler » (valeur vide) puis les niveaux de difficulté.
const choix = [
  { valeur: '', libelle: questionnaire.otHope.neutre },
  ...questionnaire.otHope.niveaux.map((n) => ({ valeur: n.id, libelle: n.libelle })),
]

function niveau(activite: string): string {
  return bilan.otHope[props.domaine]?.[activite] ?? ''
}

function coter(activite: string, valeur: string) {
  const reponses = { ...(bilan.otHope[props.domaine] ?? {}) }
  if (valeur) reponses[activite] = valeur
  else delete reponses[activite]
  bilan.otHope = { ...bilan.otHope, [props.domaine]: reponses }
}

const signalees = computed(() => Object.keys(bilan.otHope[props.domaine] ?? {}).length)
</script>

<template>
  <p class="aide">
    Pour chaque activité, « {{ questionnaire.otHope.neutre }} » ou le niveau d'aide.
    {{ signalees }} activité{{ signalees > 1 ? 's' : '' }} signalée{{ signalees > 1 ? 's' : '' }}.
  </p>
  <section class="carte activites">
    <div v-for="activite in definition.activites" :key="activite" class="activite"
         :class="{ signalee: niveau(activite) }">
      <span class="libelle">{{ activite }}</span>
      <Segments :model-value="niveau(activite)" :options="choix" :etiquette="activite"
                @update:model-value="coter(activite, $event)" />
    </div>
  </section>
</template>
