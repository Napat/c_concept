
# การค้นหาข้อมูล (Searching)  
การค้นหาข้อมูลเป็นกระบวนการค้นหา**ตำแหน่ง**ของข้อมูลที่ต้องการโดยการใช้ค่าคีย์ฟิลด์ (Key-Field) ในการค้นหาข้อมูล 
โดยจะมีความสัมพันธ์กับกระบวนการจัดเรียงลำดับข้อมูล (Sorting) ซึ่งเป็นการจัดลำดับก่อนหลังของคีย์ฟิลด์ที่กำหนดไว้ 
โดยปกติการค้นหาข้อมูลจะต้องมีการกำหนดคีย์ฟิลด์ที่ไม่ซ้ำกัน  
  
# การค้นหาข้อมูลแบบลำดับ (Sequential Search)  
คือการค้นหาข้อมูลแบบมีลำดับขั้นตอนเรียงลำดับโดยไล่ตั้งแต่ตัวแรกไปทีละตัวจนถึงตัวสุดท้ายของข้อมูลหรือจนกว่าจะพบข้อมูลที่ต้องการที่มีค่าตรงกับ
คีย์ฟิลด์ที่ต้องการหา โดยผลลัพธ์จากการค้นหาข้อมูลจึงแบ่งออกเป็น 2 คือ  
1. พบตำแหน่งข้อมูลที่ต้องการภายในลิสต์ข้อมูล(Successful Search)  
2. ไม่พบตำแหน่งข้อมูลที่ต้องการภายในลิสต์ข้อมูล (Unsuccessful Search)  
  
# การค้นหาข้อมูลแบบไบนารี่ (Binary Search)  
เป็นวิธีการค้นหาซึ่งใช้กับข้อมูลที่มีการจัดเรียงลำดับไว้เป็นที่เรียบร้อยแล้ว(เรียงจากน้อยไปมากหรือมากไปน้อยก็ได้) 
ซึ่งจะสามารถค้นหาได้เร็วกว่าการค้นหาข้อมูลแบบลำดับ  
หลักการค้นหาข้อมูลด้วยวิธีนี้คือจะทำการหาค่าตำแหน่งตรงกลางของลิสข้อมูลจากนั้นตรวจสอบว่าใช่ข้อมูลที่ต้องหริอไม่ 
หากไม่ใช่จะเปรียบเทียบค่ามากกว่าหรือน้อยกว่าเพื่อไปทำการค้นหาข้อมูลบริเวณก่อนหรือหลังตำแหน่งปัจจุบัน  
หากข้อมูลยังไม่ถูกจัดเรียงเอาไว้ก่อนสามารถทำการจัดเรียงข้อมูลก่อนด้วยเทคนิคต่างๆเช่น merge sort 
แล้วค่อยทำการเรียกใช้ binary search เพื่อค้นหาข้อมูล
