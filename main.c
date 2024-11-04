#include <stdio.h>
#include <stdint.h>


// Philips Sonicare NFC Head Password calculation by @atc1441 Video manual: https://www.youtube.com/watch?v=EPytrn8i8sc

uint16_t CRC16(uint16_t crc, uint8_t *buffer, int len) {
  while (len--) {
    crc ^= *buffer++ << 8;
    int bits = 0;
    do {
      if ((crc & 0x8000) != 0) {
        crc = (2 * crc) ^ 0x1021;
      }
      else {
        crc *= 2;
      }

    } while ( ++bits < 8);
  }
  return crc;
}

uint8_t nfctag_uid[] = {0x04,0xEC,0xFC,0xA2,0x94,0x10,0x90}; // NTAG UID
uint8_t nfc_second[] = "221214 12K";

int main() {
  uint32_t crc_calc = CRC16(0x49A3, nfctag_uid, 7);

  crc_calc = crc_calc | (CRC16(crc_calc, nfc_second, 10) << 16);

  crc_calc = (crc_calc >> 8) & 0x00FF00FF | (crc_calc << 8) & 0xFF00FF00;

  printf("by @ATC1441 NFC CRC : 0x%08X expected: 0x61F0A50F\r\n", crc_calc);

  return 0;
}
