<script setup lang="ts">
import { computed, ref, type Component } from 'vue'
import { entame, nouveauBilan, obligatoires, questionnaire, reevaluation, type Bilan } from './bilan'
import { bilan, remplacerBilan, reponsesRetirees } from './brouillon'
import Accueil from './ecrans/Accueil.vue'
import Historique from './ecrans/Historique.vue'
import Amenagements from './etapes/Amenagements.vue'
import Demande from './etapes/Demande.vue'
import Generation from './etapes/Generation.vue'
import Objectifs from './etapes/Objectifs.vue'
import OtHope from './etapes/OtHope.vue'
import Patient from './etapes/Patient.vue'
import Scolarite from './etapes/Scolarite.vue'
import Suivis from './etapes/Suivis.vue'
import { historique, type EntreeHistorique } from './historique'
import { enregistrement, reprendre } from './reprise'

interface Etape {
  titre: string
  composant: Component
  proprietes?: Record<string, string>
  /** Réponses obligatoires de l'écran, à remplir pour passer au suivant. */
  manquants?: (bilan: Bilan) => string[]
}

// Un écran OT Hope par domaine du questionnaire.
const etapes: Etape[] = [
  { titre: 'Patient', composant: Patient, manquants: obligatoires.patient },
  { titre: 'Demande', composant: Demande, manquants: obligatoires.demande },
  { titre: 'Suivis', composant: Suivis, manquants: obligatoires.suivis },
  { titre: 'Scolarité', composant: Scolarite },
  ...questionnaire.otHope.domaines.map((d) => ({
    titre: `OT Hope : ${d.titre}`, composant: OtHope, proprietes: { domaine: d.id },
  })),
  { titre: 'Objectifs', composant: Objectifs, manquants: obligatoires.objectifs },
  { titre: 'Aménagements et loisirs', composant: Amenagements },
  { titre: 'Bilan', composant: Generation },
]

const ecran = ref<'accueil' | 'saisie' | 'historique'>('accueil')
const courante = ref(0)
const etape = computed(() => etapes[courante.value])
const retireesVues = ref(false)
/** « Suivant » touché alors qu'il manquait des réponses : la liste passe en alerte. */
const tentative = ref(false)

function manquantsDe(numero: number): string[] {
  return etapes[numero].manquants?.(bilan) ?? []
}
const manquants = computed(() => manquantsDe(courante.value))
/** Dernier écran accessible : le premier dont il manque des réponses obligatoires. */
const accessible = computed(() => {
  const incomplet = etapes.findIndex((_, i) => manquantsDe(i).length > 0)
  return incomplet === -1 ? etapes.length - 1 : incomplet
})

function aller(numero: number) {
  courante.value = Math.min(numero, accessible.value)
  tentative.value = false
  window.scrollTo({ top: 0 })
}

function suivant() {
  if (manquants.value.length) tentative.value = true
  else aller(courante.value + 1)
}

/** Le bilan en cours peut être remplacé : vide, ou déjà créé en Word tel quel. */
function remplacementAccepte(): boolean {
  if (!entame(bilan)) return true
  const actuel = enregistrement(bilan)
  if (historique.value.some((entree) => entree.reponses === actuel)) return true
  return confirm(`Le bilan en cours (${bilan.prenom} ${bilan.nom}) n'a pas été créé en Word `
    + 'depuis ses dernières modifications. L\'effacer ?')
}

function commencer(nouveau: Bilan, retirees: string[] = [], numero = 0) {
  remplacerBilan(nouveau, retirees)
  retireesVues.value = false
  ecran.value = 'saisie'
  aller(numero)
}

function nouveauBilanVide() {
  if (remplacementAccepte()) commencer(nouveauBilan())
}

function reprendreEnCours() {
  retireesVues.value = reponsesRetirees.value.length === 0
  ecran.value = 'saisie'
  aller(accessible.value)
}

function relire(entree: EntreeHistorique) {
  const reprise = reprendre(entree.reponses)
  if (!reprise) alert(`Le bilan de ${entree.patient} n'a pas pu être relu.`)
  return reprise
}

function ouvrir(entree: EntreeHistorique) {
  const reprise = relire(entree)
  if (reprise && remplacementAccepte()) commencer(reprise.bilan, reprise.retirees, etapes.length - 1)
}

function reevaluer(entree: EntreeHistorique) {
  const reprise = relire(entree)
  if (reprise && remplacementAccepte()) commencer(reevaluation(reprise.bilan), reprise.retirees)
}
</script>

<template>
  <div class="haut">
    <header class="entete">
      <h1>TrameErgo</h1>
      <span v-if="ecran === 'saisie'" class="patient">{{ bilan.prenom }} {{ bilan.nom }}</span>
      <button v-if="ecran !== 'accueil'" type="button" class="accueil-lien" @click="ecran = 'accueil'">
        Accueil
      </button>
    </header>

    <nav v-if="ecran === 'saisie'" class="etapes" aria-label="Étapes du bilan">
      <button v-for="(e, i) in etapes" :key="e.titre" type="button" :disabled="i > accessible"
              :class="{ active: i === courante }" :aria-current="i === courante ? 'step' : undefined"
              @click="aller(i)">
        <span class="numero">{{ i + 1 }}</span>{{ e.titre }}
      </button>
    </nav>
  </div>

  <main>
    <Accueil v-if="ecran === 'accueil'"
             @nouveau="nouveauBilanVide" @reprendre="reprendreEnCours" @historique="ecran = 'historique'" />
    <Historique v-else-if="ecran === 'historique'" @ouvrir="ouvrir" @reevaluer="reevaluer" />
    <template v-else>
      <p v-if="reponsesRetirees.length && !retireesVues" class="bandeau alerte">
        Le questionnaire a changé : ces réponses n'existent plus et ont été retirées du bilan :
        {{ reponsesRetirees.join(', ') }}. Les choisir à nouveau si besoin.
        <button type="button" class="lien" @click="retireesVues = true">Fermer</button>
      </p>
      <h2>{{ etape.titre }}</h2>
      <Generation v-if="etape.composant === Generation" @terminer="ecran = 'accueil'" />
      <component :is="etape.composant" v-else v-bind="etape.proprietes ?? {}" :key="courante" />
      <p v-if="manquants.length" class="obligatoires">
        Pour continuer, renseigner : {{ manquants.join(', ') }}.
      </p>
    </template>
  </main>

  <footer v-if="ecran === 'saisie'" class="navigation">
    <!-- Au-dessus des boutons : visible sans faire défiler l'écran. -->
    <p v-if="tentative && manquants.length" class="alerte bloque" role="alert">
      Pour continuer, renseigner : {{ manquants.join(', ') }}.
    </p>
    <button type="button" class="secondaire" :disabled="courante === 0" @click="aller(courante - 1)">
      Précédent
    </button>
    <span>{{ courante + 1 }} / {{ etapes.length }}</span>
    <button type="button" :disabled="courante === etapes.length - 1" @click="suivant">Suivant</button>
  </footer>
</template>
