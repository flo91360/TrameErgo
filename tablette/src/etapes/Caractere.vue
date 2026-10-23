<script setup lang="ts">
// Étape facultative : caractère de l'enfant, coché par les parents puis par l'enfant.
// Les deux parties enregistrent les libellés de questionnaire.caractere ; l'écran
// les montre accordés au sexe (parents) ou reformulés simplement (enfant).
import { computed } from 'vue'
import { accord, libellesCaractere, questionnaire, type TypeCaractere } from '../bilan'
import { bilan } from '../brouillon'
import Puces from '../composants/Puces.vue'

const items = questionnaire.caractere

/** Choix des parents, montrés accordés au sexe de l'enfant. */
const accordes = computed(() => items.map((item) => accord(bilan, item.libelle, item.feminin)))
const parents = computed({
  get: () => items.filter((item) => bilan.caractereParents.includes(item.libelle))
    .map((item) => accord(bilan, item.libelle, item.feminin)),
  set: (choisis: string[]) => {
    bilan.caractereParents = items
      .filter((item) => choisis.includes(accord(bilan, item.libelle, item.feminin)))
      .map((item) => item.libelle)
  },
})

/** Choix de l'enfant d'un type (qualités ou défauts), montrés dans ses mots. */
function partieEnfant(type: TypeCaractere) {
  const duType = items.filter((item) => item.type === type)
  return {
    options: duType.map((item) => item.enfant),
    choix: computed({
      get: () => duType.filter((item) => bilan.caractereEnfant.includes(item.libelle)).map((item) => item.enfant),
      set: (choisis: string[]) => {
        const autres = bilan.caractereEnfant.filter((libelle) => !duType.some((item) => item.libelle === libelle))
        const nouveaux = duType.filter((item) => choisis.includes(item.enfant)).map((item) => item.libelle)
        bilan.caractereEnfant = libellesCaractere().filter((l) => autres.includes(l) || nouveaux.includes(l))
      },
    }),
  }
}
const qualites = partieEnfant('qualite')
const defauts = partieEnfant('defaut')
const qualitesChoisies = qualites.choix
const defautsChoisis = defauts.choix
</script>

<template>
  <p class="aide">Étape facultative : rien n'est obligatoire pour continuer.</p>

  <section class="carte">
    <h3>Selon les parents</h3>
    <p class="aide">Les parents cochent ce qui décrit {{ bilan.prenom || "l'enfant" }}.</p>
    <Puces v-model="parents" :options="accordes" />
  </section>

  <section class="carte">
    <h3>Selon l'enfant : mes qualités</h3>
    <p class="aide">{{ bilan.prenom || "L'enfant" }} coche ce qui lui ressemble.</p>
    <Puces v-model="qualitesChoisies" :options="qualites.options" />
  </section>

  <section class="carte">
    <h3>Selon l'enfant : mes défauts</h3>
    <Puces v-model="defautsChoisis" :options="defauts.options" />
  </section>
</template>
