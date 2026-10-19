<script setup lang="ts">
import { computed } from 'vue'
import { questionnaire } from '../bilan'
import { bilan } from '../brouillon'
import Puces from '../composants/Puces.vue'

const { suivis } = questionnaire

// Les puces choisissent les professionnels ; chacun garde sa fréquence de suivi,
// à renseigner pour un nouveau professionnel (pas de fréquence choisie d'office).
const suivisChoisis = computed({
  get: () => Object.keys(bilan.professionnels),
  set: (choisis: string[]) => {
    bilan.professionnels = Object.fromEntries(
      choisis.map((p) => [p, bilan.professionnels[p] ?? '']))
  },
})
</script>

<template>
  <section class="carte">
    <h3>Professionnels qui suivent l'enfant</h3>
    <Puces v-model="suivisChoisis" :options="suivis.professionnels" :desactive="bilan.aucunProfessionnel" />
    <label class="interrupteur"><input v-model="bilan.aucunProfessionnel" type="checkbox" /> Aucun</label>
  </section>

  <section v-if="!bilan.aucunProfessionnel && suivisChoisis.length" class="carte">
    <h3>Fréquence des suivis</h3>
    <div class="grille">
      <label v-for="p in suivisChoisis" :key="p">{{ p }}
        <select v-model="bilan.professionnels[p]">
          <option value="" disabled>— à renseigner —</option>
          <option v-for="f in suivis.frequences" :key="f">{{ f }}</option>
        </select>
      </label>
    </div>
  </section>
</template>
