# Use the official Node.js image as a base
FROM node:18-alpine

# Set the working directory
WORKDIR /app

# Copy package.json and package-lock.json files
COPY package*.json ./

# Install dependencies (Express and faker-js/faker)
RUN npm install --omit=dev

# Copy the application files
COPY libtransaction.js libtransaction.js

# Command to run the application
CMD ["node", "libtransaction.js"]

