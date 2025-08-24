# อาจจะต้องลบของเก่าก่อนเพื่อความชัวร์ (ถ้า build ค้าง)
rm -rf build

# สร้าง build directory ใหม่และคอมไพล์
cmake -B build
cmake --build build
