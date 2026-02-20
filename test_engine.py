import slot_engine
import random

# 1. Initialize the ReelStrip
# Assuming your C++ ReelStrip has a method to set symbols 
# or you've bound the 'Symbol' enum
try:
    strip = slot_engine.ReelStrip()
    print("ReelStrip created")
    
    # 2. Initialize a Reel at position 0
    reel = slot_engine.Reel(strip, 0)
    print("Reel created and linked to strip")

    # 3. Test a spin (if you bound a random number generator or simple spin)
    # If your C++ spin takes a seed or an int:
    # new_pos = reel.spin(random.randint(0, 1000))
    # print(f"✅ Reel spun to position: {new_pos}")

except Exception as e:
    print(f" Error: {e}")