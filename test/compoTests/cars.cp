descriptor Mechanic {
	requires {
		money : Int;
		price : Int;
		vehicleReq : { setDefectCount(n); getDefectCount(); };
	}
	provides {
		vehicleProv : { repair(defects); };
		pay : { payMoney(payment); };
	}
	service repair(defects) {
		System.println("Repairing...");
		price := defects * 50;
		vehicleReq.setDefectCount(vehicleReq.getDefectCount() - defects);
		return price;
	}
	service payMoney(payment) {
		if (payment < price) {
			System.println("$" + payment + " is not enough!");
			return false;
		}
		else {
			money := payment;
			System.println("Thank you for $" + money);
			return true;
		}
	}
}

descriptor SpecialMechanic extends Mechanic {
	service repair(defects) {
		return super.repair(defects) * 500;
	}
}

descriptor Vehicle {
	internally requires {
		color : String;
		wheelsCount : Int;
		defectCount : Int;
		mechanicReq : { repair(defects); payMoney(payment) };
	}
	internally provides {
		mechanicProv : { setDefectCount(n); getDefectCount(); };
	}
	architecture {
		connect mechanicReq to vehicleProv@(Mechanic.new());
		connect vehicleReq@mechanicReq to mechanicProv;
	}
	service setColor(newColor) {
		color := newColor;
	}
	service getColor() {
		return color;
	}
	service setWheelsCnt(n) {
		wheelsCount := n;
	}
	service getWheelsCnt() {
		return wheelsCount;
	}
	service setDefectCount(n) {
		defectCount := n;
	}
	service getDefectCount() {
		return defectCount;
	}
	service inspection() {
		|payment defects|
		System.println("You have " + defectCount + " defects, how many of them do you want to repair?");
		defects := System.readInt();
		System.println("You have to pay $" + mechanicReq.repair(defects)  + " for inspection");
		System.print("How much do you want to pay? ... ");
		while(true) {
			payment := System.readInt();
			if(mechanicReq.payMoney(payment) == true) {
				break;
			}
		}
	}
	service getVehicleInfo() {
		|res|
		res := "This vehicle is " + color + ", has " + wheelsCount + " wheels and " + defectCount + " defects";
		return res;
	}
}

descriptor Lorry extends Vehicle {
	internally requires {
		cargoKg : Int;
	}
	architecture {
		disconnect mechanicReq from vehicleProv@mechanicReq;
		disconnect vehicleReq@mechanicReq from mechanicProv;
		connect mechanicReq to vehicleProv@(SpecialMechanic.new());
		connect vehicleReq@mechanicReq to mechanicProv;
	}
	service setCargo(n) {
		cargoKg := n;
	}
	service getCargo() {
		return cargoKg;
	}
	service setWheelsCnt(n) {
		super.setWheelsCnt(n*2);
	}
	service getVehicleInfo() {
		|res|
		res := super.getVehicleInfo();
		res := res + " it is lorry and is able to carry " + cargoKg + " Kg of cargo.";
		res := res + " You will have to pay $" + 50 * 500 * defectCount + " for repair.";
		return res;
	}
}

descriptor Car extends Vehicle {
	internally requires {
		passengersCount : Int;
	}
	service setPassengers(n) {
		passengersCount := n;
	}
	service getPassengers() {
		return passengersCount;
	}
	service getVehicleInfo() {
		|res|
		res := super.getVehicleInfo();
	       	res := res + " it is Car and is able to carry " + passengersCount + " passengers";
		res := res + " You will have to pay $" + 50 * defectCount + " for repair.";
		return res;
	}
}

descriptor CompoContainer {
	service main() {
		|v1 v2 v3|
		
		v1 := Vehicle.new();
		v1.setColor("green");
		v1.setDefectCount(2);
		v1.setWheelsCnt(4);
		System.println(v1.getVehicleInfo());
		v1.inspection();
	
		System.println("");
		System.println("Lorry");
		System.println("--------------------");

		v2 := Lorry.new();
		v2.setColor("red");
		v2.setWheelsCnt(4);
		v2.setDefectCount(5);
		v2.setCargo(100);
		System.println(v2.getVehicleInfo());
		v2.inspection();
		
		System.println("");
		System.println("Car");
		System.println("--------------------");
		
		v3 := Car.new();
		v3.setColor("blue");
		v3.setWheelsCnt(6);
		v3.setDefectCount(1);
		v3.setPassengers(10);
		System.println(v3.getVehicleInfo());
		v3.inspection();
	}
}
