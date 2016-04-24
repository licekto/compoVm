descriptor Calculator {
	service add(a, b) {
		return a + b;
	}
	service sub(a, b) {
		return a - b;
	}
	service mul(a, b) {
		return a * b;
	}
	service div(a, b) {
		return a / b;
	}
	service pow(base, exp) {
		|res i|
		for (i := 0; i < exp; i := i + 1) {
			res := self.mul(res, base);
		}
		return res;
	}
	service fact(n) {
		if (n == 1) {
			return 1;
		}
		else {
			return n * self.fact(n - 1);
		}
	}
}
descriptor CompoContainer {
	service main() {
		|calc op res|
		calc := Calculator.new();
		System.println("Operation (+, -, *, /, fact)");
		op := System.readString();
		if (op == "+") {
			|op1 op2|
			System.print("Value 1: ");
			op1 := System.readInt();
			System.print("Value 2: ");
			op2 := System.readInt();
			res := calc.add(op1, op2);
		}
		else if (op == "-") {
			|op1 op2|
			System.print("Value 1: ");
			op1 := System.readInt();
			System.print("Value 2: ");
			op2 := System.readInt();
			res := calc.sub(op1, op2);
		}
		System.println(res);
		/*res := calc.add(2,3);
		System.println(res);
		System.println(calc.sub(calc.fact(4),10));*/
	}
}
