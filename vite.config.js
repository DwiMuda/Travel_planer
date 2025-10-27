import { defineConfig } from 'vite';
import vue from '@vitejs/plugin-vue';

export default defineConfig({
  plugins: [vue()],
  server: {
    watch: {
      // Ignore folder node_modules atau data besar
      ignored: ['**/node_modules/**', '**/public/data/**']
    }
  },
  optimizeDeps: {
    include: ['vue', 'vue-router'], // paksa pre-bundle dependensi yang sering dipakai
    exclude: ['some-large-lib']     // kecualikan lib yang jarang dipakai
  },
  build: {
    sourcemap: false, // matikan sourcemap untuk build lebih cepat
    chunkSizeWarningLimit: 2000, // optional, supaya tidak banyak warning
  }
});
