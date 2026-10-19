<script setup lang="ts">
import { computed } from 'vue'
import { activitesEnDifficulte, NOMBRE_OBJECTIFS, objectifsDuDomaine, objectifsPossibles, questionnaire } from '../bilan'
import { bilan } from '../brouillon'
import ChoixOrdonnes from '../composants/ChoixOrdonnes.vue'
import Segments from '../composants/Segments.vue'

const { otHope, objectifs } = questionnaire
const prenom = computed(() => bilan.prenom.trim() || "l'enfant")

// Les objectifs restent liés aux activités signalées sur les écrans OT Hope.
function objectifsDe(domaine: string) {
  return computed({
    get: () => objectifsDuDomaine(bilan, domaine),
    set: (choisis: string[]) => { bilan.objectifs = { ...bilan.objectifs, [domaine]: choisis } },
  })
}
const parDomaine = Object.fromEntries(otHope.domaines.map((d) => [d.id, objectifsDe(d.id)]))
const possibles = computed(() => objectifsPossibles(bilan))
const finaux = computed({
  get: () => bilan.objectifsFinaux.filter((o) => possibles.value.includes(o)),
  set: (choisis: string[]) => { bilan.objectifsFinaux = choisis },
})
const desParents = computed({
  get: () => bilan.objectifsParents.filter((o) => possibles.value.includes(o)),
  set: (choisis: string[]) => { bilan.objectifsParents = choisis },
})
</script>

<template>
  <p class="aide">Touchez les activités dans l'ordre de priorité ({{ NOMBRE_OBJECTIFS }} au plus).</p>
  <section v-for="domaine in otHope.domaines" :key="domaine.id" class="carte">
    <h3>Objectifs de {{ prenom }} : {{ domaine.titre.toLowerCase() }}</h3>
    <ChoixOrdonnes v-if="activitesEnDifficulte(bilan, domaine.id).length"
                   v-model="parDomaine[domaine.id].value"
                   :options="activitesEnDifficulte(bilan, domaine.id)" :maximum="NOMBRE_OBJECTIFS" />
    <p v-else class="aide">Aucune activité signalée dans ce domaine.</p>
  </section>

  <section class="carte">
    <h3>Objectifs finaux de {{ prenom }} (toutes catégories)</h3>
    <ChoixOrdonnes v-if="possibles.length" v-model="finaux" :options="possibles" :maximum="NOMBRE_OBJECTIFS" />
    <p v-else class="aide">Choisissez d'abord des objectifs ci-dessus.</p>
  </section>

  <section class="carte">
    <h3>Objectifs des parents</h3>
    <div class="champ">Les parents sont-ils en accord avec ces objectifs ?
      <Segments v-model="bilan.accordParents" etiquette="Accord des parents"
                :options="objectifs.accordParents.map((a) => ({ valeur: a.libelle, libelle: a.libelle }))" />
    </div>
    <ChoixOrdonnes v-if="possibles.length" v-model="desParents" :options="possibles" :maximum="NOMBRE_OBJECTIFS" />
    <label>Remarques des parents <textarea v-model="bilan.remarquesParents" rows="3" /></label>
  </section>
</template>
