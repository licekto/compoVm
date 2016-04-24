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
		|calc op|
		calc := Calculator.new();
		System.println("Operation (+, -, *, /, fact)");
		op := System.readString();
		System.println(op);
		/* res := calc.add(2,3);
		System.println(res);
		System.println(calc.sub(calc.fact(4),10));*/
	}
}
