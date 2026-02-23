import slot_engine
import random

try:
    strip = slot_engine.ReelStrip()
    print("ReelStrip created")
    
    reel = slot_engine.Reel(strip, 0)
    print("Reel created and linked to strip")

except Exception as e:
    print(f" Error: {e}")