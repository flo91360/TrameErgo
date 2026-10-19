<script setup lang="ts">
import { computed, ref, type Component } from 'vue'
import { questionnaire } from './bilan'
import { bilan, brouillonTrouve } from './brouillon'
import Amenagements from './etapes/Amenagements.vue'
import Demande from './etapes/Demande.vue'
import Generation from './etapes/Generation.vue'
import Objectifs from './etapes/Objectifs.vue'
import OtHope from './etapes/OtHope.vue'
import Patient from './etapes/Patient.vue'
import Scolarite from './etapes/Scolarite.vue'
import Suivis from './etapes/Suivis.vue'

interface Etape { titre: string; composant: Component; proprietes?: Record<string, string> }

// Un écran OT Hope par domaine du questionnaire.
const etapes: Etape[] = [
  { titre: 'Patient', composant: Patient },
  { titre: 'Demande', composant: Demande },
  { titre: 'Suivis', composant: Suivis },
  { titre: 'Scolarité', composant: Scolarite },
  ...questionnaire.otHope.domaines.map((d) => ({
    titre: `OT Hope : ${d.titre}`, composant: OtHope, proprietes: { domaine: d.id },
  })),
  { titre: 'Objectifs', composant: Objectifs },
  { titre: 'Aménagements et loisirs', composant: Amenagements },
  { titre: 'Bilan', composant: Generation },
]

const courante = ref(0)
const etape = computed(() => etapes[courante.value])
const brouillonRepris = ref(brouillonTrouve && !!(bilan.prenom || bilan.nom))

function aller(numero: number) {
  courante.value = numero
  window.scrollTo({ top: 0 })
}
</script>

<template>
  <header class="entete">
    <h1>TrameErgo</h1>
    <span class="patient">{{ bilan.prenom }} {{ bilan.nom }}</span>
  </header>

  <nav class="etapes" aria-label="Étapes du bilan">
    <button v-for="(e, i) in etapes" :key="e.titre" type="button"
            :class="{ active: i === courante }" :aria-current="i === courante ? 'step' : undefined"
            @click="aller(i)">
      <span class="numero">{{ i + 1 }}</span>{{ e.titre }}
    </button>
  </nav>

  <main>
    <p v-if="brouillonRepris" class="bandeau">
      Bilan en cours repris ({{ bilan.prenom }} {{ bilan.nom }}). Pour en commencer un autre :
      dernière étape, « Nouveau bilan ».
      <button type="button" class="lien" @click="brouillonRepris = false">Fermer</button>
    </p>
    <h2>{{ etape.titre }}</h2>
    <Generation v-if="etape.composant === Generation" @recommencer="brouillonRepris = false; aller(0)" />
    <component :is="etape.composant" v-else v-bind="etape.proprietes ?? {}" :key="courante" />
  </main>

  <footer class="navigation">
    <button type="button" class="secondaire" :disabled="courante === 0" @click="aller(courante - 1)">Précédent</button>
    <span>{{ courante + 1 }} / {{ etapes.length }}</span>
    <button type="button" :disabled="courante === etapes.length - 1" @click="aller(courante + 1)">Suivant</button>
  </footer>
</template>
