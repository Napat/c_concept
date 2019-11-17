
# Parsing Program argument

การจัดการ command line argument ของ C มีวิธีหลักๆที่เป็นที่นิยมดังนี้

- เขียนจัดการตัวแปร `int argc, char *argv[]` เอง โดยทั่วไปแล้วไม่แนะนำให้ใช้วิธีนี้เพราะอาจจะเขียนโปรแกรมผิดพลาดเองได้ง่าย ยกเว้นในกรณีที่ใช้งาน argument แบบ simple มากๆ

- [Getopt](https://www.gnu.org/software/libc/manual/html_node/Getopt.html#Getopt) (#include <unistd.h>) ซึ่งเป็น POSIX C library ทำให้ไม่ต้องกังวลหากต้องการ cross-plaform

- [Argp](https://www.gnu.org/software/gnulib/manual/html_node/argp_002eh.html) (#include <argp.h>) เป็น GNU C library บน Glibc สามารถทำงานที่ซับซ้อนได้ง่ายกว่า Getopt แต่อาจจะมีปัญหาเรื่อง portable ไปยัง plaform อืนๆได้

- Other libs: เช่น [opt](https://public.lanl.gov/jt/Software/), [UCW](http://www.ucw.cz/libucw/doc/ucw/), ... วิธีนี้ผู้ใช้ต้องทำ research เพิ่มเติมถึงข้อดีข้อเสียต่างๆ

## References

- https://www.gnu.org/software/libc/manual/html_node/Parsing-Program-Arguments.html
- https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c
