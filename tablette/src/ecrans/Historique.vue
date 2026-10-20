<script setup lang="ts">
import { computed, ref } from 'vue'
import { aujourdhui, dateFrancaise } from '../bilan'
import {
  historique, importer, retirerDeHistorique, sauvegarde, type EntreeHistorique,
} from '../historique'
import { enregistrerDansDocuments, surOrdinateur } from '../ordinateur'

defineEmits<{ ouvrir: [entree: EntreeHistorique]; reevaluer: [entree: EntreeHistorique] }>()

const recherche = ref('')
const message = ref('')
const entrees = computed(() => {
  const texte = recherche.value.trim().toLowerCase()
  return historique.value.filter((e) => !texte || e.patient.toLowerCase().includes(texte))
})

function creeLe(entree: EntreeHistorique): string {
  return new Date(entree.cree).toLocaleDateString('fr-FR')
}

function supprimer(entree: EntreeHistorique) {
  if (confirm(`Retirer le bilan de ${entree.patient} (${dateFrancaise(entree.passation)}) de l'historique ?`
    + ' Le fichier Word déjà créé n\'est pas touché.')) retirerDeHistorique(entree.fichier)
}

async function sauvegarder() {
  message.value = ''
  const nom = `TrameErgo_sauvegarde_${aujourdhui()}.json`
  const contenu = sauvegarde(historique.value)
  try {
    if (surOrdinateur) {
      const chemin = await enregistrerDansDocuments(nom, new TextEncoder().encode(contenu))
      message.value = `Sauvegarde enregistrée : ${chemin}`
      return
    }
    const lien = document.createElement('a')
    lien.href = URL.createObjectURL(new Blob([contenu], { type: 'application/json' }))
    lien.download = nom
    lien.click()
    setTimeout(() => URL.revokeObjectURL(lien.href), 60_000)
    message.value = `Sauvegarde créée : ${nom}`
  } catch (e) {
    message.value = `La sauvegarde n'a pas pu être enregistrée : ${e instanceof Error ? e.message : String(e)}`
  }
}

async function importerFichier(evenement: Event) {
  const champ = evenement.target as HTMLInputElement
  const fichier = champ.files?.[0]
  champ.value = ''
  if (!fichier) return
  const nombre = importer(await fichier.text())
  message.value = nombre === null
    ? `${fichier.name} n'est pas une sauvegarde de TrameErgo.`
    : `${nombre} bilan${nombre > 1 ? 's' : ''} importé${nombre > 1 ? 's' : ''}.`
}
</script>

<template>
  <h2>Historique des bilans</h2>
  <section class="carte">
    <p v-if="!historique.length" class="aide">
      Aucun bilan pour l'instant : chaque bilan Word créé sur cet appareil apparaîtra ici.
    </p>
    <template v-else>
      <label>Rechercher un patient <input v-model="recherche" type="search" autocomplete="off" /></label>
      <ul class="historique">
        <li v-for="entree in entrees" :key="entree.fichier">
          <div>
            <strong>{{ entree.patient || 'Sans nom' }}</strong>
            <span class="aide">Passation le {{ dateFrancaise(entree.passation) }}, créé le {{ creeLe(entree) }}</span>
          </div>
          <div class="boutons">
            <button type="button" class="secondaire" @click="$emit('ouvrir', entree)">Ouvrir</button>
            <button type="button" class="secondaire" @click="$emit('reevaluer', entree)">Réévaluation</button>
            <button type="button" class="danger" :aria-label="`Retirer ${entree.patient}`"
                    @click="supprimer(entree)">Retirer</button>
          </div>
        </li>
      </ul>
      <p v-if="!entrees.length" class="aide">Aucun patient ne correspond.</p>
    </template>
  </section>

  <section class="carte actions">
    <p class="aide">
      L'historique n'existe que sur cet appareil. Une sauvegarde permet de le garder à l'abri
      ou de le transférer sur un autre appareil.
    </p>
    <div class="boutons">
      <button type="button" class="secondaire" :disabled="!historique.length" @click="sauvegarder">
        Sauvegarder l'historique
      </button>
      <label class="bouton-fichier">Importer une sauvegarde
        <input type="file" accept=".json,application/json" @change="importerFichier" />
      </label>
    </div>
    <p v-if="message" class="aide" role="status">{{ message }}</p>
  </section>
</template>
