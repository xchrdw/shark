#include <pebble.h>

Window *window;
TextLayer *text_layer;

#define FRAMES 35
static int TIMER_TIMEOUT = 1000;
static uint32_t FRAME_RESOURCES[] = { 
  RESOURCE_ID_1, 
  RESOURCE_ID_2, 
  RESOURCE_ID_3,
  RESOURCE_ID_4,
  RESOURCE_ID_5,
  RESOURCE_ID_6,
  RESOURCE_ID_7,
  RESOURCE_ID_8,
  RESOURCE_ID_9,
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
static GBitmap* s_frame;
static BitmapLayer* s_bitmap_layer;

static AppTimer* s_timer;

static int s_current_frame = 0;


void handle_timer(void* data) {
  	//APP_LOG(APP_LOG_LEVEL_DEBUG, "timer");
    GBitmap* old_frame = s_frame;  
    s_current_frame = (s_current_frame+1)%FRAMES;
    s_frame = gbitmap_create_with_resource(FRAME_RESOURCES[s_current_frame]);
    if (s_frame == NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG, "error loading image");  
    }
    bitmap_layer_set_bitmap(s_bitmap_layer, s_frame);
    gbitmap_destroy(old_frame);
    s_timer = app_timer_register(TIMER_TIMEOUT, handle_timer, NULL); 		
}

void handle_init_x(void) {
	// Create a window and text layer
	window = window_create();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "window created!");   
  
  s_frame = gbitmap_create_with_resource(FRAME_RESOURCES[0]);
  s_bitmap_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_bitmap_layer, s_frame);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bitmap_layer));
  
	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
  s_timer = app_timer_register(TIMER_TIMEOUT, handle_timer, NULL); 		
}


void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);
	
  app_timer_cancel(s_timer);
  
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init_x();
	app_event_loop();
	handle_deinit();
}
