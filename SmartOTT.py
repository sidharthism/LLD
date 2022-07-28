# Smart OTT offering custom streaming platforms

# class SmartOTTp:
#     def __init__(self,):
#         self.viewing_hours_for_netflix = 0
#         self.viewing_hours_for_amazon_prime = 0
#         self.viewing_hours_for_hotstar = 0
#         self.split = ""
#         self.total_cost = 0

#     def build(self):
#         self.viewing_hours_for_netflix = int(
#             input("Viewing hours for netflix: "))
#         if self.viewing_hours_for_netflix % 10 != 0:
#             return "Viewing hours for netflix should be in multiples of 10"
#         self.viewing_hours_for_amazon_prime = int(
#             input("Viewing hours for amazon prime: "))
#         if self.viewing_hours_for_amazon_prime % 5 != 0:
#             return "Viewing hours for amazon prime should in multiples of 5"
#         self.viewing_hours_for_hotstar = int(
#             input("Viewing hours for hotstar: "))
#         if self.viewing_hours_for_hotstar % 5 != 0:
#             return "Viewing hours for hotstar should be in multiples of 5"

#         netflix_units = self.viewing_hours_for_netflix // 10
#         amazon_prime_units = self.viewing_hours_for_amazon_prime // 5
#         hotstar_units = self.viewing_hours_for_hotstar // 5

#         self.split = "( 10 * " + str(netflix_units) + " + 5 * " + \
#             str(amazon_prime_units) + " + 5 * " + str(hotstar_units) + " )"
#         self.total_cost = netflix_units * 10 + \
#             amazon_prime_units * 5 + hotstar_units * 5
#         return "Total amount should be paid: Rs." + str(self.total_cost) + " " + self.split


# smart_ott = SmartOTT()
# plan = smart_ott.build()
# print(plan)

from typing import List, Tuple


class StreamingService:
    def __init__(self, name, unitInHours, pricePerUnit):
        self._unitInHours = unitInHours
        self._pricePerUnit = pricePerUnit
        self._name = name
        self._viewingHours = 0
        self._amount = 0

    @property
    def name(self) -> str:
        return self._name

    @property
    def unitInHours(self) -> int:
        return self._unitInHours

    @property
    def pricePerUnit(self) -> int:
        return self._unitInHours

    @property
    def viewingHours(self) -> int:
        return self._viewingHours

    @property
    def noOfUnits(self) -> int:
        return 0 if self.viewingHours == 0 else (self.viewingHours // self.unitInHours)

    @property
    def amount(self) -> int:
        return self._amount

    def _validate_viewing_hours(self, hours) -> bool:
        if hours % self.unitInHours == 0:
            self._viewingHours = hours
            return True
        return False

    def _calculate_amount(self, hours) -> str:
        if self._validate_viewing_hours(int(hours)):
            self._amount = self.noOfUnits * self.pricePerUnit
            split_up = str(self.noOfUnits) + " * " + str(self.pricePerUnit)
            return (self.amount, split_up)
        else:
            raise ValueError("%s allows viewing hours in multiples of %d only" % (
                self.name, self.unitInHours))

    def subscribe(self, hours) -> Tuple[int, str]:
        return self._calculate_amount(hours)


class SmartOTT:
    def __init__(self, streamingServices: List[StreamingService]):
        self._streamingServices = [*streamingServices]
        self._total_amount = 0
        self._split_up = []

    @property
    def totalAmount(self) -> str:
        return "Rs." + str(self._total_amount)

    @property
    def splitUp(self) -> str:
        return ' + '.join(self._split_up)

    @property
    def bill(self) -> str:
        return self.totalAmount + " " + self.splitUp

    def build_subscription(self) -> Tuple[str, str]:
        for service in self._streamingServices:
            hours = int(input("Viewing hours for %s : " % service.name))
            try:
                amount, split_up = service.subscribe(hours)
                self._total_amount += amount
                self._split_up.append(split_up)
            except ValueError as e:
                print(e)
                return ("failed", "")
        return ("success", self.bill)


netflix = StreamingService("Netflix", 10, 10)
amazonPrime = StreamingService("Amazon Prime", 5, 2)
hotstar = StreamingService("Hotstar", 5, 1)

smart_ott = SmartOTT([netflix, amazonPrime, hotstar])
subscription_status, bill = smart_ott.build_subscription()
if subscription_status == "success":
    print(bill)
