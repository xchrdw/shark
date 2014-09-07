#include <pebble.h>

Window *window;
TextLayer *text_layer;

#define FRAMES 35
static int TIMER_TIMEOUT = 100;
static int FRAME_SKIP = 1;
static uint32_t FRAME_RESOURCES[] = { 
  RESOURCE_ID_01, 
  RESOURCE_ID_02, 
  RESOURCE_ID_03,
  RESOURCE_ID_04,
  RESOURCE_ID_05,
  RESOURCE_ID_06,
  RESOURCE_ID_07,
  RESOURCE_ID_08,
  RESOURCE_ID_09,
  RESOURCE_ID_10,
  RESOURCE_ID_11,
  RESOURCE_ID_12,
  RESOURCE_ID_13,
  RESOURCE_ID_14,
  RESOURCE_ID_15,
  RESOURCE_ID_16,
  RESOURCE_ID_17,
  RESOURCE_ID_18,
  RESOURCE_ID_19,
  RESOURCE_ID_20,
  RESOURCE_ID_21,
  RESOURCE_ID_22,
  RESOURCE_ID_23,
  RESOURCE_ID_24,
  RESOURCE_ID_25,
  RESOURCE_ID_26,
  RESOURCE_ID_27,
  RESOURCE_ID_28,
  RESOURCE_ID_29,
  RESOURCE_ID_30,
  RESOURCE_ID_31,
  RESOURCE_ID_32,
  RESOURCE_ID_33,
  RESOURCE_ID_34,
  RESOURCE_ID_35  
};
static GBitmap* s_frames[FRAMES];
static BitmapLayer* s_bitmap_layer;

static AppTimer* s_timer;

static int s_current_frame = 0;


void handle_timer(void* data) {
  	//APP_LOG(APP_LOG_LEVEL_DEBUG, "timer");
    s_current_frame = (s_current_frame+1+FRAME_SKIP)%FRAMES;
    bitmap_layer_set_bitmap(s_bitmap_layer, s_frames[s_current_frame]);
    s_timer = app_timer_register(TIMER_TIMEOUT, handle_timer, NULL); 		
}

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "window created");

  for (int i=0;i<FRAMES;i+=1+FRAME_SKIP) {
    // Create GBitmap, then set to created BitmapLayer
    s_frames[i] = gbitmap_create_with_resource(FRAME_RESOURCES[i]);
    if (s_frames[i] == NULL) {
      APP_LOG(APP_LOG_LEVEL_DEBUG, "error loading image");  
    } else {
      APP_LOG(APP_LOG_LEVEL_DEBUG, "img loaded");
    }
  }
  
  s_bitmap_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_bitmap_layer, s_frames[0]);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bitmap_layer));
  
	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
  s_timer = app_timer_register(TIMER_TIMEOUT, handle_timer, NULL); 		
}


void handle_deinit(void) {
  for(int i=0;i<FRAMES;i++) {
    gbitmap_destroy(s_frames[i]);  
  }  
	// Destroy the text layer
	text_layer_destroy(text_layer);
	
  app_timer_cancel(s_timer);
  
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
