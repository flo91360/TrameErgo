import { fileURLToPath, URL } from 'node:url'
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import { VitePWA } from 'vite-plugin-pwa'

// Le contenu (questionnaire.json, bilan.docx) est partagé avec l'application
// Windows : il est lu dans ../contenu, en dehors du dossier de l'application.
const contenu = fileURLToPath(new URL('../contenu', import.meta.url))

export default defineConfig({
  // Chemins relatifs : l'application fonctionne aussi dans un sous-dossier (GitHub Pages).
  base: './',
  resolve: { alias: { '@contenu': contenu } },
  server: { fs: { allow: ['..'] } },
  plugins: [
    vue(),
    VitePWA({
      registerType: 'autoUpdate',
      // Tout est mis en cache : l'application et le modèle Word marchent sans réseau.
      workbox: { globPatterns: ['**/*.{js,css,html,svg,png,docx}'] },
      manifest: {
        name: 'TrameErgo',
        short_name: 'TrameErgo',
        description: "Bilans d'ergothérapie générés sur la tablette, hors ligne",
        lang: 'fr',
        start_url: '.',
        scope: '.',
        display: 'standalone',
        orientation: 'any',
        background_color: '#f4f6f9',
        theme_color: '#1f4e79',
        icons: [
          { src: 'icone-192.png', sizes: '192x192', type: 'image/png' },
          { src: 'icone-512.png', sizes: '512x512', type: 'image/png' },
          { src: 'icone-512.png', sizes: '512x512', type: 'image/png', purpose: 'maskable' },
        ],
      },
    }),
  ],
})
