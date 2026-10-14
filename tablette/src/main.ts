import { createApp } from 'vue'
import { registerSW } from 'virtual:pwa-register'
import App from './App.vue'
import './style.css'

createApp(App).mount('#app')

// Hors ligne : l'application et le modèle Word sont mis en cache à la première visite.
registerSW({ immediate: true })
