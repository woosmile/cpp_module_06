# CPP Module 06

## 학습 내용

- C++에서의 형변환
  - static cast
  - reinterpret cast
  - dynamic cast

## 구현 내용

### ex00
- static_cast 연산자를 사용하여 char, int, float, double 간 형변환
- 형 변환 시 표현 가능 범위에 대한 예외처리

### ex01
- reinterpret_cast 연산자를 사용하여 주소 값을 정수로 바꾸고 다시 주소 값으로 바꿔서 같은 객체를 참조하는지 확인함

### ex02
- dynamic_cast 연산자를 사용하여 부모 타입을 자식 타입으로 바꿈
- 형식은 dynamic_cast 실패 시 포인터 형식은 NULL을 반환하고 레퍼런스 형식은 std::bad_cast 예외를 반환함
- 레퍼런스 형식 변환 시에 (void)&를 사용하는 이유는 변환 성공 여부만 확인하기 때문임 (컴파일 시 unused 에러 해결)
