descriptor A {

}

descriptor CompoContainer {
	service main() {
		|srv code a res p1 p2|
		srv := Service.new();
		srv.setName("testOp");
		srv.addParam("op1");
		srv.addParam("op2");

		System.println("You have service with two params (op1 and op2), write code of the service (with brackets, please): ");
		code := System.readLine();
		srv.setCode(code);
		A.addService(srv);
		a := A.new();
		
		System.print("Set first parameter: ");
		p1 := System.readInt();
		System.print("Set second parameter: ");
		p2 := System.readInt();

		System.print("Result of your code: ");
		res := a.testOp(p1, p2);
		System.println(res);
	}
}
