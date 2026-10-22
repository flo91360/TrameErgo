<script setup lang="ts">
import { ref } from 'vue'
import { enregistrerReglages, lienDeLiaison, lireLien, reglages } from '../questionnaireParents'

const emit = defineEmits<{ retour: [] }>()

const lien = ref(lienDeLiaison(reglages.value))
const erreur = ref('')

function enregistrer() {
  if (!lien.value.trim()) {
    enregistrerReglages({ adresse: '', cle: '' })
    emit('retour')
    return
  }
  const lus = lireLien(lien.value)
  if (!lus) {
    erreur.value = "Ce n'est pas un lien de liaison : coller tout le lien affiché par le script, "
      + 'qui contient « /exec#cle= ».'
    return
  }
  enregistrerReglages(lus)
  emit('retour')
}
</script>

<template>
  <h2>Questionnaire des parents</h2>
  <section class="carte">
    <p class="aide">
      Le script Google du questionnaire renvoie les réponses des parents à la création d'un bilan.
      Coller ici le lien de liaison qu'il affiche (fonction lienDeLiaison, voir formulaire/README.md),
      une fois par appareil : il reste sur l'appareil, y compris après les mises à jour. Le vider pour
      ne plus chercher de questionnaire.
    </p>
    <label>Lien de liaison
      <input v-model="lien" type="url" placeholder="https://script.google.com/macros/s/…/exec#cle=…"
             autocomplete="off" />
    </label>
    <p v-if="erreur" class="alerte" role="alert">{{ erreur }}</p>
    <div class="boutons">
      <button type="button" class="principal" @click="enregistrer">Enregistrer</button>
      <button type="button" class="secondaire" @click="emit('retour')">Annuler</button>
    </div>
  </section>
</template>
