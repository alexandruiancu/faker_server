const express = require('express');
const app = express();
const port = process.env.PORT || 3333;// use env PORT or fallback to 3333

(async () => {
  const { faker } = await import('@faker-js/faker');

  app.get('/transaction', (req, res) => {
    const data = {
      name: faker.name.findName(),
      email: faker.internet.email(),
      address: faker.address.streetAddress(),
      company: faker.company.companyName(),
      };
      res.json(data);
    });

    app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
  });
})();
