<template>
  <div>
    <!-- HEADER -->
    <header>
      <div class="header-content">
        <h1><i class="fas fa-map-marked-alt"></i> Travel Planner </h1>
        <p class="subtitle">
          Temukan destinasi wisata terbaik untuk perjalanan impian Anda
        </p>
      </div>
    </header>

    <!-- 🌿 Konten Utama -->
    <div class="container">
      <Stats
        :destination-count="filteredDestinations.length"
        :lowest-price="lowestPrice"
      />

      <!-- 🧭 3D Model -->
      <div class="model-viewer-container">
        <model-viewer
          src="/models/pura.glb"
          alt="Model 3D Pura Bali"
          auto-rotate
          camera-controls
          shadow-intensity="1"
          style="width: 100%; height: 400px; border-radius: 12px;"
        ></model-viewer>
      </div>

      <!-- 🔍 Search + Sort -->
      <div class="search-sort-container">
        <div class="search-box">
          <i class="fas fa-search"></i>
          <input
            type="text"
            v-model="currentSearch"
            placeholder="Cari destinasi wisata..."
          />
        </div>

        <div class="sort-box">
          <label for="sort-select">Urutkan:</label>
          <select id="sort-select" v-model="currentSort">
            <option value="default">Default</option>
            <option value="name-asc">Nama (A-Z)</option>
            <option value="name-desc">Nama (Z-A)</option>
            <option value="price-asc">Harga (Terendah)</option>
            <option value="price-desc">Harga (Tertinggi)</option>
          </select>
        </div>
      </div>

      <!-- 🏝️ Filter Kategori -->
      <div class="filter-bar">
        <button
          v-for="cat in categories"
          :key="cat"
          class="filter-btn"
          :class="{ active: currentCategory === cat }"
          @click="handleFilter(cat)"
        >
          {{ cat.charAt(0).toUpperCase() + cat.slice(1) }}
        </button>
      </div>

      <!-- 📋 Daftar Destinasi -->
      <DestinationList
        :destinations="filteredDestinations"
      />
    </div>

    <!-- 🌺 Footer -->
    <footer>
      <div class="footer-content">
        <h3>Travel Planner </h3>
        <p>Panduan lengkap untuk merencanakan perjalanan terbaik Anda </p>

        <div class="footer-links">
          <a href="#">Tentang Kami</a>
          <a href="#">Kebijakan Privasi</a>
          <a href="#">Syarat & Ketentuan</a>
          <a href="#">Kontak</a>
        </div>

        <div class="social-icons">
          <a href="#"><i class="fab fa-instagram"></i></a>
          <a href="#"><i class="fab fa-facebook-f"></i></a>
          <a href="#"><i class="fab fa-twitter"></i></a>
          <a href="#"><i class="fab fa-youtube"></i></a>
        </div>

        <p>&copy; 2025 Travel Planner . All rights reserved.</p>
      </div>
    </footer>
  </div>
</template>

<script>
import Stats from './components/Stats.vue';
import DestinationList from './components/DestinationList.vue';

export default {
  components: { Stats, DestinationList },
  data() {
    return {
      allDestinations: [],
      filteredDestinations: [],
      currentCategory: 'all',
      currentSort: 'default',
      currentSearch: '',
      categories: ['all', 'pantai', 'gunung', 'budaya', 'kuliner'],
      lowestPrice: 0
    };
  },
  async created() {
    try {
      const res = await fetch('/data.json');
      const data = await res.json();
      this.allDestinations = data.destinasi;
      this.filteredDestinations = [...this.allDestinations];
      this.updateStats();
    } catch (err) {
      console.error('Gagal membaca data.json', err);
    }
  },
  watch: {
    currentSearch() { this.applyFilters(); },
    currentSort() { this.applyFilters(); },
    currentCategory() { this.applyFilters(); }
  },
  methods: {
    handleFilter(category) {
      this.currentCategory = category;
    },
    applyFilters() {
      let filtered = [...this.allDestinations];

      if (this.currentCategory !== 'all') {
        filtered = filtered.filter(dest => dest.kategori === this.currentCategory);
      }

      if (this.currentSearch) {
        filtered = filtered.filter(
          dest =>
            dest.nama.toLowerCase().includes(this.currentSearch.toLowerCase()) ||
            dest.lokasi.toLowerCase().includes(this.currentSearch.toLowerCase())
        );
      }

      switch (this.currentSort) {
        case 'name-asc': filtered.sort((a, b) => a.nama.localeCompare(b.nama)); break;
        case 'name-desc': filtered.sort((a, b) => b.nama.localeCompare(a.nama)); break;
        case 'price-asc': filtered.sort((a, b) => a.harga - b.harga); break;
        case 'price-desc': filtered.sort((a, b) => b.harga - a.harga); break;
        default: filtered.sort((a, b) => a.id - b.id);
      }

      this.filteredDestinations = filtered;
      this.updateStats();
    },
    updateStats() {
      const validPrices = this.allDestinations.map(d => d.harga).filter(p => p > 0);
      this.lowestPrice = validPrices.length ? Math.min(...validPrices) : 0;
    }
  }
};
</script>