<template>
    <div class="stats">
      <div class="stat-card">
        <i class="fas fa-map-marker-alt"></i>
        <div class="number">{{ animatedDestinationCount }}</div>
        <div class="label">Destinasi</div>
      </div>
      <div class="stat-card">
        <i class="fas fa-money-bill-wave"></i>
        <div class="number">Rp{{ animatedLowestPrice.toLocaleString('id-ID') }}</div>
        <div class="label">Harga Terendah</div>
      </div>
      <div class="stat-card">
        <i class="fas fa-star"></i>
        <div class="number">4.8/5</div>
        <div class="label">Rating Pengunjung</div>
      </div>
      <div class="stat-card">
        <i class="fas fa-crown"></i>
        <div class="number">Rp{{ animatedHighestPrice.toLocaleString('id-ID') }}</div>
        <div class="label">Harga Tertinggi</div>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    props: ['destinationCount', 'lowestPrice'],
    data() {
      return {
        highestPrice: 0,
        destinations: [],
        animatedDestinationCount: 0,
        animatedLowestPrice: 0,
        animatedHighestPrice: 0,
        animationDuration: 3000, // 2 detik
        animationInterval: 20 // Update setiap 50ms
      };
    },
    mounted() {
      this.loadDestinations();
    },
    methods: {
      loadDestinations() {
        fetch('../public/data.json')
          .then(response => response.json())
          .then(data => {
            this.destinations = data.destinasi || [];
            this.calculateHighestPrice();
            this.$nextTick(() => {
              this.startAnimation();
            });
          })
          .catch(error => {
            console.error('Error loading data:', error);
            this.highestPrice = 0;
            this.animatedHighestPrice = 0;
          });
      },
      calculateHighestPrice() {
        if (this.destinations.length === 0) {
          this.highestPrice = 0;
          return;
        }
        
        // Mencari harga tertinggi dari semua destinasi
        this.highestPrice = Math.max(...this.destinations.map(d => d.harga));
      },
      startAnimation() {
        const steps = this.animationDuration / this.animationInterval;
        let currentStep = 0;

        const animateCounter = setInterval(() => {
          currentStep++;
          const progress = currentStep / steps;

          // Animasi destinationCount
          this.animatedDestinationCount = Math.floor(this.destinationCount * progress);

          // Animasi lowestPrice
          this.animatedLowestPrice = Math.floor(this.lowestPrice * progress);

          // Animasi highestPrice
          this.animatedHighestPrice = Math.floor(this.highestPrice * progress);

          if (currentStep >= steps) {
            // Set nilai final
            this.animatedDestinationCount = this.destinationCount;
            this.animatedLowestPrice = this.lowestPrice;
            this.animatedHighestPrice = this.highestPrice;
            clearInterval(animateCounter);
          }
        }, this.animationInterval);
      }
    }
  };
  </script>