import { createApp } from 'vue'
import { registerSW } from 'virtual:pwa-register'
import App from './App.vue'
import { surOrdinateur } from './ordinateur'
import './style.css'

createApp(App).mount('#app')

// Hors ligne dans un navigateur : l'application et le modèle Word sont mis en
// cache à la première visite. L'application Windows a déjà tout sur le disque.
if (!surOrdinateur) registerSW({ immediate: true })
