'use strict';

/* ══════════════════════════════════════════════
   GRAPH PRESENTATION — Navigation Controller
══════════════════════════════════════════════ */

const slides      = document.querySelectorAll('.slide');
const total       = slides.length;
let   current     = 0;
let   transitioning = false;

const btnPrev     = document.getElementById('btn-prev');
const btnNext     = document.getElementById('btn-next');
const currentEl   = document.getElementById('current-slide');
const totalEl     = document.getElementById('total-slides');
const progressEl  = document.getElementById('progress-fill');
const btnFs       = document.getElementById('btn-fullscreen');

totalEl.textContent = total;

/* ─── Core navigation ──────────────────────── */
function goTo(index) {
  if (transitioning || index < 0 || index >= total || index === current) return;
  transitioning = true;

  const prev = slides[current];
  const next = slides[index];

  prev.classList.add('exit');
  prev.classList.remove('active');

  current = index;
  next.classList.add('active');

  setTimeout(() => {
    prev.classList.remove('exit');
    transitioning = false;
  }, 460);

  updateUI();
}

const next = () => goTo(current + 1);
const prev = () => goTo(current - 1);

/* ─── UI update ─────────────────────────────── */
function updateUI() {
  currentEl.textContent = current + 1;
  progressEl.style.width = (((current + 1) / total) * 100).toFixed(2) + '%';
  btnPrev.disabled = current === 0;
  btnNext.disabled = current === total - 1;
}

/* ─── Button listeners ──────────────────────── */
btnPrev.addEventListener('click', prev);
btnNext.addEventListener('click', next);

/* ─── Keyboard navigation ───────────────────── */
document.addEventListener('keydown', e => {
  if (e.target.tagName === 'INPUT' || e.target.tagName === 'TEXTAREA') return;

  switch (e.key) {
    case 'ArrowRight':
    case 'ArrowDown':
    case ' ':
      e.preventDefault();
      next();
      break;
    case 'ArrowLeft':
    case 'ArrowUp':
      e.preventDefault();
      prev();
      break;
    case 'Home':
      e.preventDefault();
      goTo(0);
      break;
    case 'End':
      e.preventDefault();
      goTo(total - 1);
      break;
    case 'f':
    case 'F':
      toggleFullscreen();
      break;
  }
});

/* ─── Fullscreen ────────────────────────────── */
function toggleFullscreen() {
  const isFs = document.fullscreenElement || document.webkitFullscreenElement;

  if (!isFs) {
    const el = document.documentElement;
    if      (el.requestFullscreen)       el.requestFullscreen();
    else if (el.webkitRequestFullscreen) el.webkitRequestFullscreen();
  } else {
    if      (document.exitFullscreen)       document.exitFullscreen();
    else if (document.webkitExitFullscreen) document.webkitExitFullscreen();
  }
}

btnFs.addEventListener('click', toggleFullscreen);

document.addEventListener('fullscreenchange',       updateFsIcon);
document.addEventListener('webkitfullscreenchange', updateFsIcon);

function updateFsIcon() {
  const isFs = document.fullscreenElement || document.webkitFullscreenElement;
  btnFs.textContent = isFs ? '⊡' : '⛶';
  btnFs.title = isFs ? 'Sair da tela cheia (F)' : 'Tela cheia (F)';
}

/* ─── Touch / swipe ─────────────────────────── */
let touchX = 0;
let touchY = 0;

document.addEventListener('touchstart', e => {
  touchX = e.touches[0].clientX;
  touchY = e.touches[0].clientY;
}, { passive: true });

document.addEventListener('touchend', e => {
  const dx = e.changedTouches[0].clientX - touchX;
  const dy = e.changedTouches[0].clientY - touchY;

  if (Math.abs(dx) > Math.abs(dy) && Math.abs(dx) > 48) {
    dx < 0 ? next() : prev();
  }
}, { passive: true });

/* ─── Click on slide edges ──────────────────── */
document.getElementById('presentation').addEventListener('click', e => {
  const w = window.innerWidth;
  const x = e.clientX;
  const edgeZone = w * 0.12; /* 12% from each side */

  if (x < edgeZone)      prev();
  else if (x > w - edgeZone) next();
});

/* ─── Init ──────────────────────────────────── */
updateUI();
