e TH_RSE:
      if(record->event.pressed){
        raise_timer = timer_read();
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
        if (timer_elapsed(raise_timer) < 500) {
          layer_on(_RAISE);
        }
      }