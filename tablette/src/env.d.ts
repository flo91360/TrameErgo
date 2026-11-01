/// <reference types="vite/client" />

/** Version de l'application (package.json), fixée à la construction. */
declare const __VERSION__: string

declare module '*.vue' {
  import type { DefineComponent } from 'vue'
  const composant: DefineComponent<object, object, unknown>
  export default composant
}
