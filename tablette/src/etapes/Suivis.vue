<script setup lang="ts">
import { computed } from 'vue'
import { NOMBRE_AUTRES_PROFESSIONNELS, questionnaire } from '../bilan'
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

// « Autre » : thérapeutes saisis en texte libre, chacun avec sa fréquence.
const autreCoche = computed(() => bilan.autresProfessionnels.length > 0)

function basculerAutre() {
  bilan.autresProfessionnels = autreCoche.value ? [] : [{ nom: '', frequence: '' }]
}

function ajouterAutre() {
  if (bilan.autresProfessionnels.length < NOMBRE_AUTRES_PROFESSIONNELS)
    bilan.autresProfessionnels.push({ nom: '', frequence: '' })
}

function retirerAutre(i: number) {
  bilan.autresProfessionnels.splice(i, 1)
}
</script>

<template>
  <section class="carte">
    <h3>Professionnels qui suivent l'enfant</h3>
    <Puces v-model="suivisChoisis" :options="suivis.professionnels" :desactive="bilan.aucunProfessionnel">
      <button
        type="button"
        class="puce"
        :class="{ choisie: autreCoche }"
        :aria-pressed="autreCoche"
        :disabled="bilan.aucunProfessionnel"
        @click="basculerAutre"
      >
        Autre
      </button>
    </Puces>
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

  <section v-if="!bilan.aucunProfessionnel && autreCoche" class="carte">
    <h3>Autres thérapeutes</h3>
    <div v-for="(autre, i) in bilan.autresProfessionnels" :key="i" class="grille autre-therapeute">
      <label>Autre thérapeute n° {{ i + 1 }}
        <input v-model="autre.nom" placeholder="Nom ou profession" />
      </label>
      <label>Fréquence (autre thérapeute n° {{ i + 1 }})
        <select v-model="autre.frequence">
          <option value="" disabled>— à renseigner —</option>
          <option v-for="f in suivis.frequences" :key="f">{{ f }}</option>
        </select>
      </label>
      <button type="button" class="secondaire" @click="retirerAutre(i)">Retirer le n° {{ i + 1 }}</button>
    </div>
    <button
      v-if="bilan.autresProfessionnels.length < NOMBRE_AUTRES_PROFESSIONNELS"
      type="button"
      class="secondaire"
      @click="ajouterAutre"
    >
      Ajouter un autre thérapeute
    </button>
    <p v-else class="aide">{{ NOMBRE_AUTRES_PROFESSIONNELS }} autres thérapeutes au plus.</p>
  </section>
</template>

<style scoped>
.autre-therapeute { align-items: end; margin-bottom: 14px; }
</style>
