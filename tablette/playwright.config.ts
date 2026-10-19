import { defineConfig } from '@playwright/test'

// Parcours dans un vrai navigateur, sur l'application construite (npm run build).
export default defineConfig({
  testDir: 'e2e',
  testMatch: '*.e2e.ts',
  forbidOnly: !!process.env.CI,
  reporter: process.env.CI ? 'github' : 'list',
  use: {
    baseURL: 'http://localhost:4173/',
    // Tablette en paysage, au toucher.
    viewport: { width: 1024, height: 768 },
    hasTouch: true,
    locale: 'fr-FR',
    // Sans service worker : chaque test part de la version construite, sans cache.
    serviceWorkers: 'block',
    acceptDownloads: true,
  },
  webServer: {
    command: 'npx vite preview --port 4173 --strictPort',
    url: 'http://localhost:4173/',
    reuseExistingServer: !process.env.CI,
  },
})
