<template>
    <div id="list">
      <div v-if="destinations.length === 0" class="no-results">
        <i class="fas fa-search"></i>
        <h3>Tidak ada destinasi yang ditemukan</h3>
        <p>Coba ubah kata kunci pencarian atau filter kategori</p>
      </div>
  
      <div v-for="dest in destinations" :key="dest.id" class="card">
        <div class="card-image"></div>
        <span v-if="Math.random() > 0.7" class="card-badge">
          {{ badges[Math.floor(Math.random()*badges.length)] }}
        </span>
        <button class="delete-btn" @click="$emit('delete', dest.id)" title="Hapus destinasi">
          <i class="fas fa-trash-alt"></i>
        </button>
        <div class="card-content">
          <h3 class="card-title"><i class="fas fa-map-pin"></i>{{ dest.nama }}</h3>
          <div class="card-detail">
            <i class="fas fa-location-arrow"></i>
            <span>{{ dest.lokasi }}</span>
          </div>
          <div class="card-detail">
            <i class="fas fa-tags"></i>
            <span class="price">Rp{{ dest.harga.toLocaleString('id-ID') }}</span>
          </div>
          <div class="card-detail" v-if="dest.rating">
            <i class="fas fa-star"></i>
            <span>Rating: {{ dest.rating }}/5</span>
          </div>
        </div>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    props: ['destinations'],
    data() {
      return { badges: ['Populer', 'Favorit', 'Baru', 'Terjangkau'] };
    }
  };
  </script>
  