import { defineConfig, devices } from '@playwright/test'

// Parcours dans un vrai navigateur, sur l'application construite (npm run build).
export default defineConfig({
  testDir: 'e2e',
  testMatch: '*.e2e.ts',
  forbidOnly: !!process.env.CI,
  reporter: process.env.CI ? 'github' : 'list',
  use: {
    baseURL: 'http://localhost:4173/',
    locale: 'fr-FR',
    // Sans service worker : chaque test part de la version construite, sans cache.
    serviceWorkers: 'block',
    acceptDownloads: true,
  },
  projects: [
    // Tablette Android et application Windows (WebView2) : moteur Chromium, au toucher.
    { name: 'chromium', use: { browserName: 'chromium', viewport: { width: 1024, height: 768 }, hasTouch: true } },
    // iPad : moteur WebKit, celui de Safari.
    { name: 'ipad', use: { ...devices['iPad (gen 7) landscape'] } },
  ],
  webServer: {
    command: 'npx vite preview --port 4173 --strictPort',
    url: 'http://localhost:4173/',
    reuseExistingServer: !process.env.CI,
  },
})
