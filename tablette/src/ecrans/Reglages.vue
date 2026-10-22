<script setup lang="ts">
import { ref } from 'vue'
import { enregistrerReglages, reglages } from '../questionnaireParents'

const emit = defineEmits<{ retour: [] }>()

const adresse = ref(reglages.value.adresse)
const cle = ref(reglages.value.cle)
const erreur = ref('')

function enregistrer() {
  const valide = (() => {
    try {
      return new URL(adresse.value.trim()).protocol === 'https:'
    } catch {
      return false
    }
  })()
  if (adresse.value.trim() && !valide) {
    erreur.value = "L'adresse doit commencer par https:// (adresse de l'application web, qui finit par /exec)."
    return
  }
  enregistrerReglages({ adresse: adresse.value, cle: cle.value })
  emit('retour')
}
</script>

<template>
  <h2>Questionnaire des parents</h2>
  <section class="carte">
    <p class="aide">
      Le script Google du questionnaire renvoie les réponses des parents à la création d'un bilan.
      Coller ici l'adresse de son application web et sa clé, affichées lors de son installation
      (voir formulaire/README.md). Les deux restent sur cet appareil. Les laisser vides pour ne plus
      chercher de questionnaire.
    </p>
    <label>Adresse de l'application web
      <input v-model="adresse" type="url" placeholder="https://script.google.com/macros/s/…/exec" autocomplete="off" />
    </label>
    <label>Clé <input v-model="cle" autocomplete="off" /></label>
    <p v-if="erreur" class="alerte" role="alert">{{ erreur }}</p>
    <div class="boutons">
      <button type="button" class="principal" @click="enregistrer">Enregistrer</button>
      <button type="button" class="secondaire" @click="emit('retour')">Annuler</button>
    </div>
  </section>
</template>
