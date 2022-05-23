#include <lcom/lab5.h>
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "vc.h"

// The only func failing the tests is the last.

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  if (lcf_start(argc, argv))
    return 1;
  lcf_cleanup();
  return 0;
}

// sets video card to given graphic MODE for DELAY
// seconds and returns back to minix's default text mode
int(video_test_init)(uint16_t mode, uint8_t delay) {

  // set video card graphic mode
  if (set_vc_mode(mode)) {
    printf("Error changing to video mode.\n");
    return 1;
  }

  sleep(delay); // wait delay seconds to exit graphic mode

  // return to minix's text mode
  if (vg_exit()) {
    printf("Error exiting graphic mode into text mode.\n");
    return 1;
  }

  return 0;
}

// you should consider only the 24 least significant bits, i.e. the 3 least significant bytes, of the color argument if in OX115 MODE!!!
int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

  if (set_graphics_card_mode(mode)) {
    vg_exit();
    return 1;
  }

  /*
    // pinta fundo do ecra de vermelho
    if (vg_draw_fill(0xFF0000))
      return 1;
  */

  if (vg_draw_rectangle(x, y, width, height, color))
    return 1;

  // sleep(5); // temporary replacement for the ESC scancode (0x81)
  waitForEscPress();

  // return to minix's text mode
  if (vg_exit()) {
    printf("Error exiting graphic mode into text mode.\n");
    return 1;
  }

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

  //  lcom_run lab5 "pattern 14C 20 005000 6"
  //  lcom_run lab5 "pattern 105 10 4 1"

  // for rainbow use
  // lcom_run lab5 "pattern 14C 255 0 1"

  if (set_graphics_card_mode(mode)) {
    vg_exit();
    return 1;
  }

  // execute...
  video_pattern(no_rectangles, first, step);

  // sleep(5); // temporary replacement for the ESC scancode (0x81)
  waitForEscPress();

  // return to minix's text mode
  if (vg_exit()) {
    printf("Error exiting graphic mode into text mode.\n");
    return 1;
  }

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

  // lcom_run lab5 "xpm 4 400 170"

  // tem de ser o indexado pq e assim que as cores estao
  // definidas nos arrays pixmap dados pelos stores
  if (set_graphics_card_mode(INDEXED_COLOR)) {
    vg_exit();
    return 1;
  }

  // no trabalho vamos usar XPM_8_8_8_8, 0x14C --> cores hexadecimais e transparencia
  xpm_image_t img;
  uint8_t *map = xpm_load(xpm, XPM_INDEXED, &img);

  if (map == NULL)
    return 1;

  // pinta o xpm loaded com as cores certas guardadas em *map
  for (unsigned i = 0; i < img.height; i++)
    for (unsigned j = 0; j < img.width; j++)
      changePixelColor(x + j, y + i, *map++);

  /*
  No modo direto: XPM_8_8_8_8, 0x14C
// Estamos a considerar 4 bytes para cor / pixel
RGB rgb = RGB_new(0);
rgb.setBlue(&rgb, *map);
map++;
rgb.setGreen(&rgb, *map);
map++;
rgb.setRed(&rgb, *map);
map++;

// verifica se transparencia tem valor definido (modo XPM_8_8_8_8)
if (!*map++) {
changePixelColor(x + j, y + i, rgb.value);
}
*/
  // no modo indexado é so um map++. No direto, temos 1byte para cada parte da cor: R G B Transparency

  // notar que estamos a percorrer a altura e comprimento da imagem
  //  e no processo incrementando o *map (ou seja saltando para a proxima)
  //  cor a ser usada no proximo changePixelColor

  // sleep(5); // temporary replacement for the ESC scancode (0x81)
  waitForEscPress();

  // return to minix's text mode
  if (vg_exit()) {
    printf("Error exiting graphic mode into text mode.\n");
    return 1;
  }

  return 0;
}

extern unsigned counter; // Timer counter

// lcom_run lab5 "move 4 10:10 300:10 1:60"
int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate) {

  // carregar xpm
  xpm_image_t img;
  uint8_t *map = xpm_load(xpm, XPM_INDEXED, &img);

  if (set_graphics_card_mode(0x105)) {
    vg_exit();
    return 1;
  }

  // pintar a imagem inicial
  for (unsigned int height = 0; height < img.height; height++)
    for (unsigned int width = 0; width < img.width; width++)
      changePixelColor(xi + width, yi + height, *map++);

  // variaveis para movimento
  moveCords_t cords = {.xi = xi, .yi = yi, .xf = xf, .yf = yf, .newX = xi, .newY = yi};

  // vars para interrupts
  uint8_t bit_no_timer = 0, bit_no_kbd = 0;
  int ipc_status, r;
  message msg;

  // vars para ler os bytes scancode
  bool another_read = false;
  uint8_t codes[2];

  // subscrever interrupts
  timer_subscribe_int(&bit_no_timer);
  kbd_subscribe_int(&bit_no_kbd);

  while (scancode != ESC_BREAKCODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {

      // KBD Interrupt
      if (msg.m_notify.interrupts & BIT(bit_no_kbd)) {

        kbc_ih(); // chamar o nosso handler

        if (!another_read) {
          codes[0] = scancode;
          if (scancode == MSB_2B_SCANCODE)
            another_read = true;
        }
        else {
          codes[1] = scancode;
          another_read = false;
        }
      }

      // Timer Interrupt
      if (msg.m_notify.interrupts & BIT(bit_no_timer))
        if (cords.newX != xf || cords.newY != yf) {

          timer_int_handler();

          if (counter % (sys_hz() / fr_rate) == 0)
            XPMmove(xpm, &cords, speed, fr_rate);
        }
    }
  }

  timer_unsubscribe_int();
  kbd_unsubscribe_int();

  return vg_exit();
}
