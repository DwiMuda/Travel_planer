<template>
    <div class="search-sort-container">
      <div class="search-box">
        <i class="fas fa-search"></i>
        <input type="text" placeholder="Cari destinasi wisata..."
               v-model="searchLocal" @input="$emit('update:search', searchLocal)" />
      </div>
      <div class="sort-box">
        <label for="sort-select">Urutkan:</label>
        <select v-model="sortLocal" @change="$emit('update:sort', sortLocal)">
          <option value="default">Default</option>
          <option value="name-asc">Nama (A-Z)</option>
          <option value="name-desc">Nama (Z-A)</option>
          <option value="price-asc">Harga (Terendah)</option>
          <option value="price-desc">Harga (Tertinggi)</option>
        </select>
      </div>
  
      <div class="filter-bar">
        <button v-for="cat in categories" :key="cat"
                :class="{ active: cat===activeCategory }"
                @click="$emit('filter', cat)">
          {{ cat === 'all' ? 'Semua' : cat.charAt(0).toUpperCase() + cat.slice(1) }}
        </button>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    props: ['categories', 'activeCategory', 'search', 'sort'],
    data() { return { searchLocal: this.search, sortLocal: this.sort }; }
  };
  </script>
  