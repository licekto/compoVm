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
		res := 1;
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
		while (true) {
			System.println("Operation (+, -, *, /, fact, pow, q)");
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
			else if (op == "*") {
				|op1 op2|
				System.print("Value 1: ");
				op1 := System.readInt();
				System.print("Value 2: ");
				op2 := System.readInt();
				res := calc.mul(op1, op2);
			}
			else if (op == "/") {
				|op1 op2|
				System.print("Value 1: ");
				op1 := System.readInt();
				System.print("Value 2: ");
				op2 := System.readInt();
				res := calc.div(op1, op2);
			}
			else if (op == "pow") {
				|op1 op2|
				System.print("Value 1: ");
				op1 := System.readInt();
				System.print("Value 2: ");
				op2 := System.readInt();
				res := calc.pow(op1, op2);
			}
			else if (op == "fact") {
				|op|
				System.print("Value: ");
				op := System.readInt();
				res := calc.fact(op);
			}
			else if (op == "q") {
				System.println("Quit");
				break;
			}
			else {
				System.println("Wrong operation!");
			}
			System.println(res);
		}
	}
}
